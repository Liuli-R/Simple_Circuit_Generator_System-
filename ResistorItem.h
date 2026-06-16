#ifndef RESISTORITEM_H
#define RESISTORITEM_H

#include "ComponentItem.h"

class ResistorItem:public ComponentItem
{
    public:
        ResistorItem(int ResistorId,QGraphicsItem *parent=nullptr);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;
};

#endif // RESISTORITEM_H
