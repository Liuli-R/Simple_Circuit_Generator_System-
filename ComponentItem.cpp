#include "ComponentItem.h"

ComponentItem::ComponentItem(int componentId,QGraphicsItem *parent)
{

}

int ComponentItem::getComponentId() const
{
    return id;
}

QRectF ComponentItem::boundingRect() const
{
    return QRectF();
}
