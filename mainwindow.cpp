#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "circuitscene.h"
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QIcon>
#include <QDebug>
#include <QList>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScene();
    setupComponentActions();
    setupComponentPanel();
    setupRunButton();
    setupHeader();
    setupConnections();
}

void MainWindow::setupScene()
{
    scene=new CircuitScene(this);
    //把生成场景对象交给CircuitScene处理
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setSceneRect(scene->sceneRect());
}

void MainWindow::setupComponentActions()
{
    //将所有的QAction*->行为集中在一起放入列表作为功能存储
    bulbAction=new QAction(QIcon(":/Cpp_Practice_Picture/Bulb.png"),"小灯泡",this);
    switchAction=new QAction(QIcon(":/Cpp_Practice_Picture/Switch.png"),"开关",this);
    batteryAction=new QAction(QIcon(":/Cpp_Practice_Picture/Battery.png"),"电源",this);
    ammeterAction=new QAction(QIcon(":/Cpp_Practice_Picture/ammeter.png"),"电流表",this);
    voltmeterAction=new QAction(QIcon(":/Cpp_Practice_Picture/voltmeter 0-3v.png"),"电压表",this);
    resistorAction=new QAction(QIcon(":/Cpp_Practice_Picture/resistor.png"),"电阻",this);
}

QToolButton * MainWindow::createComponentButton(QAction *action)
{
    QToolButton *button = new QToolButton(this);
    button->setDefaultAction(action);
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    button->setIconSize(QSize(56, 40));
    button->setFixedSize(92, 82);
    button->setObjectName("componentButton");
    return button;
}

void MainWindow::setupComponentPanel()
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

void MainWindow::setupRunButton()
{
    //设置runAction的目的是如果后续想添加多个方式进行运行直接绑定
    //runAction指针指向的QAction即可，享有相同的触发效果，图标，快捷键等
    runAction = new QAction(QIcon(":/Cpp_Practice_Picture/run.png"), "运行", this);
    runAction->setToolTip("运行当前电路并刷新灯泡状态"); //小字提示部分
    runAction->setShortcut(QKeySequence("Ctrl+R")); //快捷键

    QToolButton *runButton = new QToolButton(this);
    runButton->setDefaultAction(runAction);//按钮默认绑定动作
    runButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//图片在文字旁边
    runButton->setAutoRaise(true);//按钮鼠标放上或按下自动凸起
    runButton->setCursor(Qt::PointingHandCursor);//图标变为指向手
    runButton->setObjectName("runButton");
    /*这个形式类似setText设置文本内容，但是实际作用相当于是
     设计给程序识别的对象名字内容，方便匹配到QSS中的美化样式*/

    ui->menubar->setCornerWidget(runButton, Qt::TopRightCorner);//设置到菜单栏的右边位置
}

void MainWindow::setupHeader()
{
    ui->headerFrame->setObjectName("componentHeader");
    //便于css单独设计(实际是qss但是qss无法高亮显示又由于qt只需保证语法无误，所以采用css)
    ui->iconLabel->setPixmap(QPixmap(":/Cpp_Practice_Picture/Tool.png").scaled(20, 20,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    //图像平滑变换
    ui->titleLabel->setObjectName("componentHeaderTitle");
}

void MainWindow::setupConnections()
{
    connect(runAction, &QAction::triggered, this, [=]() {
        ui->statusbar->showMessage("运行电路ing~~~",3000);  //提醒注释:Qt中时间以毫秒结尾
    });//将"运行电路"信息重新写道底下状态栏中
}

MainWindow::~MainWindow()
{
    delete ui;
}
