#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene=new QGraphicsScene(this);
    QGraphicsEllipseItem *circle=scene->addEllipse(0,0,80,80);
    circle->setFlag(QGraphicsItem::ItemIsMovable);
    circle->setFlag(QGraphicsItem::ItemIsSelectable);
    QGraphicsView *view=new QGraphicsView(scene,this);
    setCentralWidget(view);

    addToolBar(Qt::LeftToolBarArea,ui->toolBar);
    ui->toolBar->setMovable(false);

    QAction *bulbAction=new QAction(QIcon(":/Cpp_Practice_Picture/Bulb.png"),"小灯泡",this);
    ui->toolBar->addAction(bulbAction);
    ui->toolBar->setIconSize(QSize(60,40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->addSeparator();

    QAction *switchAction=new QAction(QIcon(":/Cpp_Practice_Picture/Switch.png"),"开关",this);
    ui->toolBar->addAction(switchAction);
    ui->toolBar->setIconSize(QSize(60,40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->addSeparator();

    QAction *batteryAction=new QAction(QIcon(":/Cpp_Practice_Picture/Battery.png"),"电源",this);
    ui->toolBar->addAction(batteryAction);
    ui->toolBar->setIconSize(QSize(60,40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->addSeparator();

    QAction *amaterAction=new QAction(QIcon(":/Cpp_Practice_Picture/ammeter.png"),"电流表",this);
    ui->toolBar->addAction(amaterAction);
    ui->toolBar->setIconSize(QSize(60,40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->addSeparator();

    QAction *voltmeterAction=new QAction(QIcon(":/Cpp_Practice_Picture/voltmeter 0-3v.png"),"电压表",this);
    ui->toolBar->addAction(voltmeterAction);
    ui->toolBar->setIconSize(QSize(60,40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->addSeparator();

    QAction *resistorAction=new QAction(QIcon(":/Cpp_Practice_Picture/resistor.png"),"电阻",this);
    ui->toolBar->addAction(resistorAction);
    ui->toolBar->setIconSize(QSize(60,40));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBar->addSeparator();

    ui->toolBar->setFixedWidth(90);

    //设置runAction的目的是如果后续想添加多个方式进行运行直接绑定
    //runAction指针指向的QAction即可，享有相同的触发效果，图标，快捷键等
    QAction *runAction = new QAction(QIcon(":/Cpp_Practice_Picture/run.png"), "运行", this);
    runAction->setToolTip("运行当前电路并刷新灯泡状态"); //小字提示部分
    runAction->setShortcut(QKeySequence("Ctrl+R")); //快捷键

    QToolButton *runButton = new QToolButton(this);
    runButton->setDefaultAction(runAction);//按钮默认绑定动作
    runButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//图片在文字旁边
    runButton->setAutoRaise(true);//按钮鼠标放上或按下自动凸起
    runButton->setCursor(Qt::PointingHandCursor);//图标变为指向手

    ui->menubar->setCornerWidget(runButton, Qt::TopRightCorner);//设置到菜单栏的右边位置

    connect(runAction, &QAction::triggered, this, [=]() {
        ui->statusbar->showMessage("运行电路ing~~~",3000);
        //提醒注释:Qt中时间以毫秒结尾
    });//将"运行电路"信息重新写道底下状态栏中

    runButton->setObjectName("runButton");
    /*这个形式类似setText设置文本内容，但是实际作用相当于是
     设计给程序识别的对象名字内容，方便匹配到QSS中的美化样式*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
