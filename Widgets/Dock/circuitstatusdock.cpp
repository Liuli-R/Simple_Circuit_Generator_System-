#include "circuitstatusdock.h"
#include "ui_circuitstatusdock.h"

#include <QMovie>
#include <QSize>
#include <QString>
#include <QSignalBlocker>
//新学习到->信号阻塞的一个类

CircuitStatusDock::CircuitStatusDock(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::CircuitStatusDock)
{
    ui->setupUi(this);

    connect(ui->voltmeterComboBox,&QComboBox::currentIndexChanged,
            this,&CircuitStatusDock::updateSelectedVoltmeter);
    setupAnimation();
    resetDisplay();
}

CircuitStatusDock::~CircuitStatusDock()
{
    delete ui;
}

void CircuitStatusDock::setupAnimation()
{
    movie = new QMovie(this);
    movie->setFileName(":/Cpp_Practice_Picture/Loading.gif");
    movie->setScaledSize(QSize(260, 260));
    movie->setCacheMode(QMovie::CacheAll);

    if (!movie->isValid())
    {
        ui->gifLabel->setText("动画资源加载失败");
        return;
    }

    ui->gifLabel->setMovie(movie);
    movie->start();
}

void CircuitStatusDock::updateSelectedVoltmeter(int index)
{
    if (index < 0 || index >= static_cast<int>(voltmeterResults.size()))
    {
        ui->targetValueLabel->setText("未设置");
        ui->readingValueLabel->setText("-- V");
        return;
    }

    const auto &meter = voltmeterResults[index];

    ui->targetValueLabel->setText(meter.hasTarget? QString("元器件 #%1")
        .arg(meter.targetComponentId): "未设置");

    ui->readingValueLabel->setText(meter.hasTarget?
        QString::number(meter.reading, 'f', 2) + " V": "-- V");
}

void CircuitStatusDock::resetDisplay()
{
    ui->stateValueLabel->setText("未运行");
    ui->totalVoltageValueLabel->setText("-- V");
    ui->resistanceValueLabel->setText("-- Ω");
    ui->currentValueLabel->setText("-- A");
    ui->targetValueLabel->setText("未设置");
    ui->readingValueLabel->setText("-- V");

    voltmeterResults.clear();

    QSignalBlocker blocker(ui->voltmeterComboBox);
    //暂停阻止中间信号 最后将中间信号汇总并阻断抛弃
    ui->voltmeterComboBox->clear();
    ui->voltmeterComboBox->setPlaceholderText("暂无电压表");
    ui->voltmeterComboBox->setCurrentIndex(-1);
}

void CircuitStatusDock::updateResult(const CircuitSolveResult &result)
{
    switch (result.state)
    {
        case CircuitRunState::NotRun:
            resetDisplay();
            return;
        case CircuitRunState::Open:
            ui->stateValueLabel->setText("电路未闭合");
            break;
        case CircuitRunState::MissingBattery:
            ui->stateValueLabel->setText("缺少电源");
            break;
        case CircuitRunState::InvalidResistance:
            ui->stateValueLabel->setText("无有效电阻");
            break;
        case CircuitRunState::Running:
            ui->stateValueLabel->setText("电路闭合运行");
            break;
    }

    //统一精确单位到后两位小数
    if (result.state == CircuitRunState::MissingBattery)
        ui->totalVoltageValueLabel->setText("-- V");
    else
        ui->totalVoltageValueLabel->setText(QString::number(result.totalVoltage, 'f', 2) + " V");

    if (result.totalResistance > 0.0)
        ui->resistanceValueLabel->setText(QString::number(result.totalResistance, 'f', 2) + " Ω");
    else
        ui->resistanceValueLabel->setText("-- Ω");

    if (result.state != CircuitRunState::Running)
        ui->currentValueLabel->setText("不可用");
    else if (!result.hasAmmeter)
        ui->currentValueLabel->setText("缺少电流表");
    else
        ui->currentValueLabel->setText(QString::number(result.current, 'f', 2) + " A");

    //新版改为对多个电压表兼容的判断版本
    voltmeterResults = result.voltmeters;

    //新知识点->大括号作用域作为独立作用域 拥有独立的生命周期
    {
        QSignalBlocker blocker(ui->voltmeterComboBox);
        ui->voltmeterComboBox->clear();
        for (const auto &meter : voltmeterResults)
            ui->voltmeterComboBox->addItem(QString("电压表 #%1").arg(meter.voltmeterId));

        if (voltmeterResults.empty())
        {
            ui->voltmeterComboBox->setPlaceholderText
                (result.hasVoltmeter? "暂无可用读数": "暂无电压表");
            ui->voltmeterComboBox->setCurrentIndex(-1);
        }//index指的是条目设置 图形化界面的下拉条目
        else
            ui->voltmeterComboBox->setCurrentIndex(0);
    }

    // 7. 数据全部准备完成后，主动刷新一次显示
    updateSelectedVoltmeter(ui->voltmeterComboBox->currentIndex());
}
