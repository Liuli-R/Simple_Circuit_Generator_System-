#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
