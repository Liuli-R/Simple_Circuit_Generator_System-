#include "VoltmeterItem.h"

#include <QPainter>
VoltmeterItem::VoltmeterItem(int VoltmeterId,QGraphicsItem *parent)
    :ComponentItem(VoltmeterId,parent)
{
}

void VoltmeterItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    drawTerminals(painter);

    painter->setPen(QPen(QColor(17, 24, 39), 2.4));
    painter->setBrush(QColor(255, 255, 255));
    painter->drawEllipse(QPointF(0, 0), 30, 30);

    //画代表电流表的字母'V'
    QFont font;
    font.setPointSize(26);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(QRectF(-30,-30,60,60),Qt::AlignCenter,"V");

    painter->setPen(QPen(QColor(75, 85, 99), 1.5));
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(QRectF(-55, 36, 110, 20), Qt::AlignCenter, QString("电压表 #%1").arg(getComponentId()));
    //原理同前
}
int VoltmeterItem::getVoltage() const
{
    return voltage;
}
void VoltmeterItem::setVoltage(double vol)
{
    voltage=vol;
}
QRectF VoltmeterItem::boundingRect() const
{
    return QRectF(-78,-68,156,136);
}

