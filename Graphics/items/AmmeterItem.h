#ifndef AMMETERITEM_H
#define AMMETERITEM_H

#include "ComponentItem.h"

class AmmeterItem:public ComponentItem
{
    public:
        AmmeterItem(int AmmeterId,QGraphicsItem *parent=nullptr);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        int getCurrent() const;
        void setCurrent(double cur);
        QRectF boundingRect() const override;
    private:
        double current=0.0;
};

#endif // AMMETERITEM_H
