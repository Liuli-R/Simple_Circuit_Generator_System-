#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Application/ComponentAddController.h"
#include "Graphics/scene/circuitscene.h"
#include "Graphics/manager/ComponentItemManager.h"
#include "Graphics/manager/WireManager.h"
#include "Graphics/items/BulbItem.h"
#include "Graphics/layout/CircuitLayout.h"
#include "Graphics/layout/circuitlayoutbuilder.h"
#include "Circuit_code/Bulb.h"
#include "Circuit_code/Switch.h"
#include "Circuit_code/Battery.h"
#include "Circuit_code/Voltmeter.h"
#include "Circuit_code/Fixed_resistor.h"
#include "Widgets/TopBar/topactionwidget.h"
#include "Widgets/Palette/componentpalettewidget.h"
#include "Widgets/Dock/circuitstatusdock.h"
#include "Widgets/Dialog/circuitsettingsdialog.h"
#include "Widgets/Dialog/guidedialog.h"
#include "Widgets/Dialog/circuitsettingsdialog.h"

#include <QMenu>
#include <QAction>
#include <QGraphicsView>
#include <QIcon>
#include <QKeySequence>
#include <QPainter>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScene();
    setupActions();
    setupMenus();
    setupTopActionWidget();
    setupStatusDock();
    setupConnections();
}

void MainWindow::setupScene()
{
    scene = new CircuitScene(this);
    //把生成场景对象交给CircuitScene处理
    ui->graphicsView->setScene(scene);
    itemManager = new ComponentItemManager(scene);
    wireManager = new WireManager(scene);
    componentAddController = new ComponentAddController(circuit, *itemManager);
    componentAddController->setSwitchStateChangedCallback([this](){updateCircuitState();});
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setSceneRect(scene->sceneRect());
}

void MainWindow::setupActions()
{
    //设置runAction的目的是如果后续想添加多个方式进行运行直接绑定
    //runAction指针指向的QAction即可，享有相同的触发效果，图标，快捷键等
    runAction = new QAction(QIcon(":/Cpp_Practice_Picture/run.png"), "运行", this);
    runAction->setToolTip("运行当前电路并刷新灯泡状态");
    runAction->setShortcut(QKeySequence("Ctrl+R"));

    clearAction = new QAction(QIcon(":/Cpp_Practice_Picture/clear.png"), "清空", this);
    clearAction->setToolTip("清空当前电路和画布");
    clearAction->setShortcut(QKeySequence("Ctrl+L"));

    settingsAction = new QAction(QIcon(":/Cpp_Practice_Picture/settings.png"),"电路参数",this);
    settingsAction->setToolTip("设置当前电路基本参数");
    settingsAction->setShortcut(QKeySequence("Ctrl+,"));

    guideAction = new QAction(QIcon(":/Cpp_Practice_Picture/help.png"),"使用说明",this);
    guideAction->setToolTip("这里是项目说明呦!");
    guideAction->setShortcut(QKeySequence(Qt::Key_F1));
}

void MainWindow::setupMenus()
{
    QMenu *operationMenu = new QMenu("操作", this);
    QMenu *settingsMenu = new QMenu("设置", this);
    QMenu *helpMenu = new QMenu("帮助", this);
    operationMenu->addSeparator();
    settingsMenu->addSeparator();
    helpMenu->addSeparator();
    ui->menubar->addMenu(operationMenu);
    ui->menubar->addMenu(settingsMenu);
    ui->menubar->addMenu(helpMenu);
    operationMenu->addAction(runAction);
    operationMenu->addAction(clearAction);
    settingsMenu->addAction(settingsAction);
    helpMenu->addAction(guideAction);
}

void MainWindow::setupTopActionWidget()
{
    topActionWidget = new TopActionWidget(this);
    topActionWidget->setRunAction(runAction);
    topActionWidget->setClearAction(clearAction);

    ui->menubar->setCornerWidget(topActionWidget, Qt::TopRightCorner);
}

void MainWindow::setupStatusDock()
{
    statusDock = new CircuitStatusDock(this);
    addDockWidget(Qt::RightDockWidgetArea,statusDock);
}

void MainWindow::setupConnections()
{
    connect(runAction, &QAction::triggered, this, [=]() {
        ui->statusbar->showMessage("运行电路ing~~~", 3000);  //提醒注释:Qt中时间以毫秒结尾
        runCircuit();
    });//将"运行电路"信息重新写道底下状态栏中
    connect(clearAction, &QAction::triggered, this, [=]() {
        ui->statusbar->showMessage("清除电路状态成功√", 3000);
        clearCircuit();
    });
    connect(settingsAction,&QAction::triggered,this,&MainWindow::openSettingsDialog);
    connect(guideAction,&QAction::triggered,this,&MainWindow::openGuideDialog);
    //点击对应设置该行为的按钮打开窗口
    connect(ui->componentPalette, &ComponentPaletteWidget::bulbRequested, this, [this]() {
        componentAddController->addBulb();
    });
    connect(ui->componentPalette, &ComponentPaletteWidget::switchRequested, this, [this]() {
        componentAddController->addSwitch();
    });
    connect(ui->componentPalette, &ComponentPaletteWidget::batteryRequested, this, [this]() {
        componentAddController->addBattery();
    });
    connect(ui->componentPalette, &ComponentPaletteWidget::ammeterRequested, this, [this]() {
        componentAddController->addAmmeter();
    });
    connect(ui->componentPalette, &ComponentPaletteWidget::voltmeterRequested, this, [this]() {
        componentAddController->addVoltmeter();
    });
    connect(ui->componentPalette, &ComponentPaletteWidget::resistorRequested, this, [this]() {
        componentAddController->addResistor();
    });
}

bool MainWindow::areAllSwitchesClosed() const
{
    bool allClosed = true;
    for (auto comp : circuit.getMainLoopComponents())
    {
        auto *sw = dynamic_cast<Switch *>(comp);
        if (sw != nullptr && !sw->isClosed())
            allClosed = false;
    }//有一个不闭合全电路就是非闭合状态反之就是默认闭合通路
    return allClosed;
}//完善检查逻辑只有电路中所有开关全部闭合才能控制一系列状态

bool MainWindow::isCircuitClosed() const
{
    return circuit.isClosedLoop() && areAllSwitchesClosed() && circuit.hasBattery();
}//统一判断多个条件是否满足成立电路运行

CircuitLayout MainWindow::buildCircuit()
{
    CircuitLayoutBuilder builder;
    CircuitLayout layout = builder.build(circuit,*itemManager,scene->sceneRect());
    circuit.buildClosedLoop(layout.orderedComponentIds());
    return layout;
}

void MainWindow::runCircuit()
{
    wireManager->clearWires();
    wireManager->drawSeriesWires(buildCircuit());
    wireManager->drawVoltmeterWires(circuit,*itemManager);
    auto result=solver.solve(circuit, areAllSwitchesClosed());
    statusDock->updateResult(result);
    updateScene();
    circuitPrepared = true;
}

void MainWindow::clearCircuit()
{
    wireManager->clearWires();
    circuit.clearCircuit();
    componentAddController->resetIds();
    if (itemManager != nullptr)
        itemManager->clearAll();
    statusDock->resetDisplay();
    circuitPrepared = false;
    //否则第二次边界测试会出现没连线开关就直接控制灯泡亮暗
}

void MainWindow::updateCircuitState()
{
    if (!circuitPrepared)
        return;
    buildCircuit();
    auto result=solver.solve(circuit, areAllSwitchesClosed());
    statusDock->updateResult(result);
    updateScene();
}

void MainWindow::updateScene()
{
    for (auto comp : circuit.getMainLoopComponents())
    {
        auto *bb = dynamic_cast<Bulb *>(comp);
        if (bb == nullptr)
            continue;
        auto compItem = dynamic_cast<BulbItem *>(itemManager->findItemByComponentId(bb->getId()));
        compItem->setLightOn(bb->isLitState());
    }
}

void MainWindow::openSettingsDialog()
{
        CircuitSettingsDialog dialog(this);

        dialog.setInitialVoltage(componentAddController->getDefaultBatteryVoltage());

        for (auto *component : circuit.getComponents())
        {
            if (component == nullptr)
                continue;

            QString typeName = QString::fromStdString(component->getTypeName());

            if (typeName == "voltmeter")
            {
                dialog.addVoltmeterOption(component->getId());
                continue;
            }//寻找电压表并加入到对应voltageComBox中

            if (typeName == "resistor")
            {
                dialog.addResistorOption(component->getId());
                dialog.addTargetOption(component->getId(),QString("%1 #%2").arg(typeName).arg(component->getId()));
                continue;
            }//寻找定值电阻并加入到对应resistorComBox中

            if (typeName == "bulb")
                dialog.addTargetOption(component->getId(),QString("%1 #%2").arg(typeName).arg(component->getId()));
        }

        if (dialog.exec() != QDialog::Accepted)
            return;
        //如果界面选择cancel那么就直接不设置，反之则直接生成存储设置结构体改动信息

        CircuitSettings settings = dialog.settings();

        componentAddController->setDefaultBatteryVoltage(settings.batteryVoltage);

        for (auto *component : circuit.getComponents())
        {
            auto *battery =dynamic_cast<Battery *>(component);

            if (battery != nullptr)
                battery->setVoltage(settings.batteryVoltage);
        }

        if (settings.voltmeterId >= 0 && settings.targetComponentId >= 0)
        {
            buildCircuit();
            auto *meter = dynamic_cast<Voltmeter *>(circuit.findComponentById(settings.voltmeterId));
            auto *target = circuit.findComponentById(settings.targetComponentId);
            circuit.connectVoltmeterTo(meter,target);
            /*可能出现bug的地方->由于buildClosedLoop是根据实际排布重新排序
            所以需要做的点就是可能会导模型图形连线重新建立，但是实际元器件并为同步*/
            //原因是target采用的仍然是原先最开始分配的node节点顺序
            QPointF targetcenter = itemManager->findItemByComponentId(settings.targetComponentId)
                ->sceneBoundingRect().center();
            itemManager->findItemByComponentId(settings.voltmeterId)->setPos(targetcenter.x(),targetcenter.y()-120);
        }

        if (settings.resistorId >= 0)
        {
            auto *resistor = dynamic_cast<Fixed_resistor *>(circuit.findComponentById(settings.resistorId));

            if (resistor != nullptr)
                resistor->setResistance(settings.resistance);
        }

        wireManager->clearWires();
        solver.resetOutputs(circuit);
        updateScene();

        circuitPrepared = false;
        statusDock->resetDisplay();
}

void MainWindow::openGuideDialog()
{
    GuideDialog dialog(this);
    dialog.exec();
}

Circuit &MainWindow::getCircuit()
{
    return circuit;
}

const Circuit &MainWindow::getCircuit() const
{
    return circuit;
}

MainWindow::~MainWindow()
{
    delete componentAddController;
    delete wireManager;
    delete itemManager;
    delete ui;
}
