#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Application/ComponentAddController.h"
#include "Graphics/scene/circuitscene.h"
#include "Graphics/manager/ComponentItemManager.h"
#include "Graphics/manager/WireManager.h"
#include "componentpalettewidget.h"
#include "Circuit_code/Bulb.h"
#include "Circuit_code/switch.h"
#include "Graphics/items/BulbItem.h"
#include "topactionwidget.h"

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
}

void MainWindow::setupMenus()
{
    QMenu *operationMenu = ui->menubar->addMenu("操作");
    operationMenu->addAction(runAction);
    operationMenu->addAction(clearAction);
}

void MainWindow::setupTopActionWidget()
{
    topActionWidget = new TopActionWidget(this);
    topActionWidget->setRunAction(runAction);
    topActionWidget->setClearAction(clearAction);

    ui->menubar->setCornerWidget(topActionWidget, Qt::TopRightCorner);
}

void MainWindow::setupConnections()
{
    connect(runAction, &QAction::triggered, this, [=]() {
        ui->statusbar->showMessage("运行电路ing~~~", 3000);  //提醒注释:Qt中时间以毫秒结尾
        runCircuit();
    });//将"运行电路"信息重新写道底下状态栏中
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

void MainWindow::buildCircuit()
{
    circuit.buildClosedLoop();
}

void MainWindow::runCircuit()
{
    buildCircuit();
    wireManager->clearWires();
    wireManager->drawSeriesWires(circuit, *itemManager);
    solver.solve(circuit, isCircuitClosed());
    updateScene();
}

void MainWindow::clearCircuit()
{
    wireManager->clearWires();
    circuit.clearCircuit();
    componentAddController->resetIds();
    if (itemManager != nullptr)
        itemManager->clearAll();
}

void MainWindow::updateCircuitState(bool switchClosed)
{
    buildCircuit();
    solver.solve(circuit, switchClosed);
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
