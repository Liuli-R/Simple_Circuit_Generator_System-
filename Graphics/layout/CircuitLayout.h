#ifndef CIRCUITLAYOUT_H
#define CIRCUITLAYOUT_H

#include <QPointF>
#include <QRectF>
#include "ComponentLayout.h"

struct CircuitLayout
{
    std::vector<ComponentLayout> orderedItems;
    //存储从图中排序完毕的图形元器件
    qreal leftRouteX = 0.0;//图形左边界-一定距离安全范围
    qreal rightRouteX = 0.0;//图形右边界+一定距离安全范围
    qreal bottomRouteY = 0.0;//底部边界+一定距离安全范围

    std::vector<int> orderedComponentIds() const
    {
        std::vector<int> ids;
        for (const auto &item : orderedItems)
            ids.push_back(item.componentId);
        return ids;
    }//返回排序好的元器件id
};
#endif // CIRCUITLAYOUT_H
