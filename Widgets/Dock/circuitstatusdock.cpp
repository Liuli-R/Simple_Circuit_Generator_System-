#include "circuitstatusdock.h"
#include "ui_circuitstatusdock.h"

#include "Circuit_code/CircuitSolveResult.h"

#include <QMovie>
#include <QSize>
#include <QString>

CircuitStatusDock::CircuitStatusDock(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::CircuitStatusDock)
{
    ui->setupUi(this);

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

void CircuitStatusDock::resetDisplay()
{
    ui->stateValueLabel->setText("未运行");
    ui->totalVoltageValueLabel->setText("-- V");
    ui->resistanceValueLabel->setText("-- Ω");
    ui->currentValueLabel->setText("-- A");
    ui->voltageValueLabel->setText("-- V");
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

    if (result.state != CircuitRunState::Running)
        ui->voltageValueLabel->setText("不可用");
    else if (!result.hasVoltmeter)
        ui->voltageValueLabel->setText("缺少电压表");
    else if (!result.voltmeterHasTarget)
        ui->voltageValueLabel->setText("未设置测量目标");
    else
        ui->voltageValueLabel->setText(QString::number(result.voltmeterReading, 'f', 2) + " V");
}