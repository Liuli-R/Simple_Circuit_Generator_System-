#include "AmmeterItem.h"

#include <QPainter>

AmmeterItem::AmmeterItem(int AmmeterId, QGraphicsItem *parent)
    : ComponentItem(AmmeterId, parent)
{
}

void AmmeterItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    drawTerminals(painter);

    painter->setPen(QPen(QColor(17, 24, 39), 2.4));
    painter->setBrush(QColor(255, 255, 255));
    painter->drawEllipse(QPointF(0, 0), 30, 30);

    //画代表电流表的字母'A'
    QFont font;
    font.setPointSize(26);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(QRectF(-30, -30, 60, 60), Qt::AlignCenter, "A");

    painter->setPen(QPen(QColor(75, 85, 99), 1.5));
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(QRectF(-55, 36, 110, 20), Qt::AlignCenter, QString("电流表 #%1").arg(getComponentId()));
    //原理同前
}

int AmmeterItem::getCurrent() const
{
    return current;
}

QRectF AmmeterItem::boundingRect() const
{
    return QRectF(-78, -68, 156, 136);
}

void AmmeterItem::setCurrent(double cur)
{
    current = cur;
}
