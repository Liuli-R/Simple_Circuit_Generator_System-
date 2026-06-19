#include "componentpalettewidget.h"
#include "ui_componentpalettewidget.h"

#include <QIcon>
#include <QPixmap>
#include <QList>
#include <QToolButton>

ComponentPaletteWidget::ComponentPaletteWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ComponentPaletteWidget)
{
    ui->setupUi(this);
    setupComponentActions();
    setupComponentPanel();
    setupHeader();
    setupConnections();
}

void ComponentPaletteWidget::setupComponentActions()
{
    bulbAction = new QAction(QIcon(":/Cpp_Practice_Picture/Bulb.png"), "小灯泡", this);
    switchAction = new QAction(QIcon(":/Cpp_Practice_Picture/Switch.png"), "开关", this);
    batteryAction = new QAction(QIcon(":/Cpp_Practice_Picture/Battery.png"), "电源", this);
    ammeterAction = new QAction(QIcon(":/Cpp_Practice_Picture/ammeter.png"), "电流表", this);
    voltmeterAction = new QAction(QIcon(":/Cpp_Practice_Picture/voltmeter 0-3v.png"), "电压表", this);
    resistorAction = new QAction(QIcon(":/Cpp_Practice_Picture/resistor.png"), "电阻", this);
}

QToolButton *ComponentPaletteWidget::createComponentButton(QAction *action)
{
    QToolButton *button = new QToolButton(this);
    button->setDefaultAction(action);
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    button->setIconSize(QSize(56, 40));
    button->setFixedSize(100, 92);
    button->setObjectName("componentButton");
    return button;
}

void ComponentPaletteWidget::setupComponentPanel()
{
    ui->componentPanel->setObjectName("componentPanel");
    ui->componentScrollArea->setObjectName("componentScrollArea");
    QList<QAction *> componentActions =
        {
            bulbAction,
            switchAction,
            batteryAction,
            ammeterAction,
            voltmeterAction,
            resistorAction
        };//模板参数为QAction*
    for(QAction* iterator:componentActions)
    {
        ui->componentLayout->addWidget(createComponentButton(iterator));
    }
    ui->componentLayout->addStretch();
}

void ComponentPaletteWidget::setupHeader()
{
    ui->headerFrame->setObjectName("componentHeader");
    ui->iconLabel->setObjectName("componentHeaderIcon");
    //便于css单独设计(实际是qss但是qss无法高亮显示又由于qt只需保证语法无误，所以采用css)
    ui->iconLabel->setPixmap(QPixmap(":/Cpp_Practice_Picture/Tool.png").scaled(18, 18,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    //图像平滑变换
    ui->titleLabel->setObjectName("componentHeaderTitle");
}

void ComponentPaletteWidget::setupConnections()
{
    connect(bulbAction, &QAction::triggered, this, &ComponentPaletteWidget::bulbRequested);
    connect(switchAction, &QAction::triggered, this, &ComponentPaletteWidget::switchRequested);
    connect(batteryAction, &QAction::triggered, this, &ComponentPaletteWidget::batteryRequested);
    connect(ammeterAction, &QAction::triggered, this, &ComponentPaletteWidget::ammeterRequested);
    connect(voltmeterAction, &QAction::triggered, this, &ComponentPaletteWidget::voltmeterRequested);
    connect(resistorAction, &QAction::triggered, this, &ComponentPaletteWidget::resistorRequested);
}

ComponentPaletteWidget::~ComponentPaletteWidget()
{
    delete ui;
}
