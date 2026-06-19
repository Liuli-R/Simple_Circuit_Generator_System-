#ifndef VOLTMETERITEM_H
#define VOLTMETERITEM_H

#include "ComponentItem.h"

class VoltmeterItem : public ComponentItem
{
public:
    VoltmeterItem(int VoltmeterId, QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int getVoltage() const;
    void setVoltage(double vol);
    QRectF boundingRect() const override;

private:
    double voltage = 0.0;
};

#endif // VOLTMETERITEM_H
