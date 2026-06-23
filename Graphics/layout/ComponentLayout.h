#ifndef COMPONENTLAYOUT_H
#define COMPONENTLAYOUT_H

#include <QPointF>
#include <QRectF>

struct ComponentLayout
{
    int componentId = -1;
    QPointF leftPoint;
    QPointF rightPoint;
    QRectF sceneBounds;//元器件图案的图形边界
    qreal centerY = 0.0;
    int rowIndex = -1;//默认排列行号
};

#endif // COMPONENTLAYOUT_H
