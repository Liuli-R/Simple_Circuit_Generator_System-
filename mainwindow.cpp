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
}

MainWindow::~MainWindow()
{
    delete ui;
}
