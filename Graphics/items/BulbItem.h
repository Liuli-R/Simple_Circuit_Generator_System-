#ifndef BULBITEM_H
#define BULBITEM_H

#include "ComponentItem.h"

class BulbItem : public ComponentItem
{
public:
    BulbItem(int BulbId, QGraphicsItem *parent = nullptr);
    void setLightOn(bool state);//设置
    bool isLightOn() const;//访问
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    bool lightOn = false;
};

#endif // BULBITEM_H
