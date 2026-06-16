#include "BatteryItem.h"

#include <QPainter>
BatteryItem::BatteryItem(int BatteryId, QGraphicsItem *parent)
    :ComponentItem(BatteryId,parent)
{
}

void BatteryItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    //抗锯齿使图片边缘更光滑清楚
    drawTerminals(painter);

    QPen pen(QColor(0,0,0),3.0,Qt::SolidLine,Qt::RoundCap);
    //声明并定义一个黑色，线宽3.0，实线，圆头
    painter->setPen(pen);
    //拿笔画线长直线与短直线代表电源正负极
    painter->drawLine(QPointF(-18, -32), QPointF(-18, 32));
    painter->drawLine(QPointF(14, -22), QPointF(14, 22));

    //表示电源正负极符号
    painter->setPen(QPen(QColor(75, 85, 99), 1.5));
    //设置字体并重新设置字号加粗
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(QRectF(-55, 30, 110, 20), Qt::AlignCenter, QString("电源 #%1").arg(getComponentId()));
    //标明每个元器件的名称及编号
    font.setPointSize(20);
    painter->setFont(font);
    //重新设置字体为了更直观地显示对应的正负号
    painter->drawText(QPointF(-30, -36), "+");
    painter->drawText(QPointF(10, -32), "-");
}
