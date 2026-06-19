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
    ui->runButton->setObjectName("runButton");
    /*这个形式类似setText设置文本内容，但是实际作用相当于是
     设计给程序识别的对象名字内容，方便匹配到QSS中的美化样式*/
}

void TopActionWidget::setClearAction(QAction *action)
{
    ui->clearButton->setDefaultAction(action);//按钮默认绑定动作
    ui->clearButton->setObjectName("clearButton");
}

TopActionWidget::~TopActionWidget()
{
    delete ui;
}