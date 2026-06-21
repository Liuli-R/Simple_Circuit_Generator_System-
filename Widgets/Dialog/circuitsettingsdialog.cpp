#include "circuitsettingsdialog.h"
#include "ui_circuitsettingsdialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QPixmap>

CircuitSettingsDialog::CircuitSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CircuitSettingsDialog)
{
    ui->setupUi(this);
    /*在ui界面已经设置了关于voltageSpinBox->keyboardtracking->false 便于用户
    可以最终模态确定其结果再更新数据，否则将实时更新数据，与目标不符，且占用开销*/
    ui->voltmeterComboBox->setPlaceholderText("请选择电压表");
    ui->targetComboBox->setPlaceholderText("请选择测量目标");
    //添加默认灰色字代表初始->文字提示
    setupPicture();

    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&CircuitSettingsDialog::validateAndAccept);
    connect(ui->buttonBox,&QDialogButtonBox::rejected,this,&QDialog::reject);
}

CircuitSettingsDialog::~CircuitSettingsDialog()
{
    delete ui;
}

void CircuitSettingsDialog::setInitialVoltage(double voltage)
{
    ui->voltageSpinBox->setValue(voltage);
}

void CircuitSettingsDialog::addVoltmeterOption(int componentId)
{
    ui->voltmeterComboBox->addItem(QString("电压表 #%1").arg(componentId),componentId);
}

void CircuitSettingsDialog::addTargetOption(int componentId,const QString &displayText)
{
    ui->targetComboBox->addItem(displayText,componentId);
}

CircuitSettings CircuitSettingsDialog::settings() const
{
    CircuitSettings result;

    result.batteryVoltage = ui->voltageSpinBox->value();

    if (ui->voltmeterComboBox->currentIndex() >= 0)//currentData返回的是QVariant转换成int
        result.voltmeterId = ui->voltmeterComboBox->currentData().toInt();

    if (ui->targetComboBox->currentIndex() >= 0)
        result.targetComponentId = ui->targetComboBox->currentData().toInt();

    return result;
}

void CircuitSettingsDialog::validateAndAccept()
{
    if (ui->voltmeterComboBox->count() > 0 && ui->voltmeterComboBox->currentIndex() < 0)
    {//ui界面默认初始设置index为-1即代表没有
        ui->hintLabel->setText("请选择需要设置的电压表");
        return;
    }

    if (ui->voltmeterComboBox->count() > 0 && ui->targetComboBox->currentIndex() < 0)
    {//ui界面默认初始设置index为1即代表有
        ui->hintLabel->setText("请选择电压表的测量目标");
        return;
    }

    ui->hintLabel->clear();
    accept();
}

void CircuitSettingsDialog::setupPicture()
{
    QPixmap picture(":/Cpp_Practice_Picture/Point_Introdution.png");

    if (picture.isNull())
    {
        ui->pictureLabel->setText("设置图片");
        return;
    }

    ui->pictureLabel->setPixmap(picture.scaled(190,280,Qt::KeepAspectRatio,Qt::SmoothTransformation));
}