#include "BulbItem.h"

#include <QPainter>

BulbItem::BulbItem(int BulbId,QGraphicsItem *parent)
    :ComponentItem(BulbId,parent)
{
}

bool BulbItem::isLightOn() const
{
    return lightOn;
}

void BulbItem::setLightOn(bool state)
{
    if (lightOn == state)
    {
        return;
    }

    lightOn=state;
    //用来设置新的状态进而更新状态
    update();
}

QRectF BulbItem::boundingRect() const
{
    return QRectF(-78,-68,156,136);
}

void BulbItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);

    if (lightOn)
    {
        //创建黄色光晕进行由中心扩散边缘来表示灯泡发光
        QRadialGradient glow(QPointF(0, 0), 58);
        glow.setColorAt(0.0, QColor(253, 224, 71, 150));
        glow.setColorAt(1.0, QColor(253, 224, 71, 0));
        //0.0是中心 1.0是边缘 0.0-1.0表示作用范围距离 相对glow的点而言
        painter->setPen(Qt::NoPen);
        painter->setBrush(glow);
        painter->drawEllipse(QPointF(0, 0), 58, 58);
    }

    drawTerminals(painter);

    //再在光晕上创建一个纯色圆(亮为黄色不亮为白色)
    painter->setPen(QPen(QColor(17, 24, 39), 2.4));
    painter->setBrush(lightOn ? QColor(254, 240, 138) : QColor(255, 255, 255));
    painter->drawEllipse(QPointF(0, 0), 30, 30);

    //画相应的线表示
    painter->drawLine(QPointF(-17, -17), QPointF(17, 17));
    painter->drawLine(QPointF(-17, 17), QPointF(17, -17));

    painter->setPen(QPen(QColor(75, 85, 99), 1.5));
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(QRectF(-55, 36, 110, 20), Qt::AlignCenter, QString("Bulb #%1").arg(getComponentId()));
    //原理同前
}


