#include "WireManager.h"

#include "Circuit_code/Circuit.h"
#include "Circuit_code/Component.h"
#include "Graphics/items/ComponentItem.h"
#include "Graphics/manager/ComponentItemManager.h"

#include <QColor>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QLineF>
#include <QPen>
#include <QPointF>

#include <cstddef>

WireManager::WireManager(QGraphicsScene *scene)
    : scene(scene)
{
}

void WireManager::clearWires()
{
    for (auto *wire : wireItems)
    {
        if (wire != nullptr)
        {
            scene->removeItem(wire);
            delete wire;
        }
    }
    wireItems.clear();
}

void WireManager::drawSeriesWires(const Circuit &circuit, const ComponentItemManager &itemManager)
{
    auto components = circuit.getMainLoopComponents();
    QPointF start,end;

    if (components.size() < 2)//边界处理
        return;

    QPen wirePen(QColor(31, 41, 55), 2.2, Qt::SolidLine, Qt::RoundCap);

    for (std::size_t i = 0; i < components.size(); i++)
    {
        Component *current = components[i];
        Component *next = components[(i + 1) % components.size()];//与Node同思路闭合画线

        ComponentItem *currentItem = itemManager.findItemByComponentId(current->getId());
        ComponentItem *nextItem = itemManager.findItemByComponentId(next->getId());

        if (currentItem == nullptr || nextItem == nullptr)
            continue;

        if(i<components.size()-2)
        {
            start = currentItem->rightPointScenePos();
            end = nextItem->leftPointScenePos();
        }
        else if(i==components.size()-2)
        {
            start = currentItem->rightPointScenePos();
            end = nextItem->rightPointScenePos();
        }
        else
        {
            start = currentItem->leftPointScenePos();
            end = nextItem->leftPointScenePos();
        }
        auto *wire = scene->addLine(QLineF(start, end), wirePen);
        wire->setZValue(-1);//设置其显示在元器件图层之下

        wireItems.push_back(wire);
    }
}
