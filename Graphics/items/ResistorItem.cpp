#include "ResistorItem.h"

#include <QPainter>

ResistorItem::ResistorItem(int ResistorId, QGraphicsItem *parent)
    : ComponentItem(ResistorId, parent)
//参数列表默认值声明一次即可
{
}

void ResistorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    //抗锯齿使图片边缘更光滑清楚
    drawTerminals(painter);

    QPen pen(QColor(0, 0, 0), 2.4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    //最后一个参数进行圆角平滑连接
    painter->setPen(pen);
    painter->setBrush(QColor(255, 255, 255));
    painter->drawRoundedRect(QRectF(-35, -18, 70, 36), 5, 5);
    /*内部用白色填充电阻的内部，填充白色的原因即防止因调用
    drawTerminals而导致保持绿色填充*/

    painter->setPen(QPen(QColor(75, 85, 99), 1.5));
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(QRectF(-55, 30, 110, 20), Qt::AlignCenter, QString("定值电阻 #%1").arg(getComponentId()));
}
