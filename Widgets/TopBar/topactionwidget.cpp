#include "topactionwidget.h"
#include "ui_topactionwidget.h"

#include <QAction>
#include <QToolButton>

TopActionWidget::TopActionWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TopActionWidget)
{
    ui->setupUi(this);
}

void TopActionWidget::setRunAction(QAction *action)
{
    ui->runButton->setDefaultAction(action);//按钮默认绑定动作
}

void TopActionWidget::setClearAction(QAction *action)
{
    ui->clearButton->setDefaultAction(action);//按钮默认绑定动作
}

TopActionWidget::~TopActionWidget()
{
    delete ui;
}
