#ifndef BATTERYITEM_H
#define BATTERYITEM_H

#include "ComponentItem.h"

class BatteryItem : public ComponentItem
{
public:
    BatteryItem(int BatteryId, QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    //重写接口绘制函数->作区分这是提供给QGraphicsItem的
    //而有一个功能相似的PaintEvent是提供给QWidget的
};

#endif // BATTERYITEM_H
