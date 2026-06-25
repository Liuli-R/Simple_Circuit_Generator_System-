#include "SwitchItem.h"

#include <QPainter>
#include <utility>
//用来严谨配合移动语义的

SwitchItem::SwitchItem(int SwitchId, QGraphicsItem *parent)
    : ComponentItem(SwitchId, parent)
{
}

bool SwitchItem::isClosed() const
{
    return closed;
}

void SwitchItem::setClosed(bool state)
{
    if (closed == state)
    {
        return;
    }

    closed = state;
    //用来设置新的状态进而更新状态
    update();
}

//点睛之笔->用处双击从模型状态同步到数据开关的状态->回调函数
void SwitchItem::setStateChangedCallback(std::function<void(int, bool)> callback)
{
    stageChangedCallback = std::move(callback);
    //这里就调用了拷贝构造 赋值运算符
    //也可以考虑通过移动语义进行移动构造
}
/*加深了这一块cpp用法的理解，function本质也是一种容器但是装的是函数对象
也就是把外部的广义函数对象存进去，然后就能建立内部调用联系*/

void SwitchItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    //抗锯齿使图片边缘更光滑清楚
    drawTerminals(painter);

    //用来模拟开关导线旁边的空心小白点(实际是用白色填充替代实心小白点)
    QPen pen(QColor(0, 0, 0), 2.4, Qt::SolidLine, Qt::RoundCap);
    painter->setPen(pen);
    painter->setBrush(QColor(255, 255, 255));
    painter->drawEllipse(QPointF(-26, 0), 5, 5);
    painter->drawEllipse(QPointF(26, 0), 5, 5);

    //模拟开关开关的动作图形变更
    if (closed)
    {
        painter->drawLine(QPointF(-21, 0), QPointF(21, 0));
    }
    else
    {
        painter->drawLine(QPointF(-21, 0), QPointF(20, -24));
    }

    //根据现有开关状态判断是否调整笔的颜色红色还是绿色
    painter->setPen(QPen(closed ? QColor(22, 163, 74) : QColor(220, 38, 38), 1.6));
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    //百分号起到占位符的通用类似c语言
    painter->drawText(QRectF(-60, 30, 120, 20), Qt::AlignCenter, QString("Switch #%1 %2").arg(getComponentId()).arg(closed ? "closed" : "open"));
}

void SwitchItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    isClosed() ? setClosed(false) : setClosed(true);
    if (stageChangedCallback)//防止空指针的情况
    {
        stageChangedCallback(getComponentId(), closed);
        //更新传入函数的形参状态从而方便调用
    }

    QGraphicsItem::mouseDoubleClickEvent(event);
}
