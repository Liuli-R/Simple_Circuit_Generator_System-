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
    ui->toolBar->setFixedWidth(90);
    ui->toolBar->addSeparator();
}

MainWindow::~MainWindow()
{
    delete ui;
}
