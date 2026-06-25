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
    ui->resistorComboBox->setPlaceholderText("请选择电阻");
    ui->horizontalLayout->setAlignment(ui->pictureLabel,Qt::AlignVCenter);
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

void CircuitSettingsDialog::setInitialResistance(double resistance)
{
    ui->resistanceSpinBox->setValue(resistance);
}

void CircuitSettingsDialog::addVoltmeterOption(int componentId)
{
    ui->voltmeterComboBox->addItem(QString("电压表 #%1").arg(componentId),componentId);
}

void CircuitSettingsDialog::addResistorOption(int componentId)
{
    ui->resistorComboBox->addItem(QString("定值电阻 #%1").arg(componentId),componentId);
}

void CircuitSettingsDialog::addTargetOption(int componentId,const QString &displayText)
{
    ui->targetComboBox->addItem(displayText,componentId);
}

CircuitSettings CircuitSettingsDialog::settings() const
{
    CircuitSettings result;

    result.batteryVoltage = ui->voltageSpinBox->value();
    result.resistance = ui->resistanceSpinBox->value();

    if (ui->voltmeterComboBox->currentIndex() >= 0)//currentData返回的是QVariant转换成int
        result.voltmeterId = ui->voltmeterComboBox->currentData().toInt();

    if (ui->targetComboBox->currentIndex() >= 0)
        result.targetComponentId = ui->targetComboBox->currentData().toInt();

    if (ui->resistorComboBox->currentIndex() >= 0)
        result.resistorId = ui->resistorComboBox->currentData().toInt();
    return result;
}

void CircuitSettingsDialog::validateAndAccept()
{
    bool hasSelectedVoltmeter = ui->voltmeterComboBox->currentIndex() >= 0;
    bool hasSelectedTarget = ui->targetComboBox->currentIndex() >= 0;
    bool hasVoltmeterOptions = ui->voltmeterComboBox->count() > 0;
    bool hasTargetOptions = ui->targetComboBox->count() > 0;
    if (hasSelectedTarget && !hasVoltmeterOptions)
    {
        ui->hintLabel->setText("当前电路无可用电压表");
        return;
    }
    if (hasSelectedVoltmeter && !hasTargetOptions)
    {
        ui->hintLabel->setText("当前电路无可用测量目标");
        return;
    }
    if(hasSelectedVoltmeter != hasSelectedTarget)
    {
        ui->hintLabel->setText("若设置电压表，请同时选择电压表和测量目标");
        return ;
    }
    //更改为更符合用户设计的设置窗口
    ui->hintLabel->clear();
    accept();
}

void CircuitSettingsDialog::setupPicture()
{
    QPixmap picture(":/Cpp_Practice_Picture/Point_Introduction_Portrait.png");

    if (picture.isNull())
    {
        ui->pictureLabel->setText("设置图片");
        return;
    }

    ui->pictureLabel->setPixmap(picture.scaled(200,300,Qt::KeepAspectRatio,Qt::SmoothTransformation));
}
