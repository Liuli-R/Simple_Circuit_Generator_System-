#include "WireManager.h"
#include "Circuit_code/Circuit.h"
#include "Circuit_code/Component.h"
#include "Circuit_code/Voltmeter.h"
#include "Graphics/layout/CircuitLayout.h"
#include "Graphics/items/ComponentItem.h"
#include "Graphics/manager/ComponentItemManager.h"

#include <QColor>
#include <QPainter>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QLineF>
#include <QPen>
#include <QPointF>

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

void WireManager::drawVoltmeterWires(const Circuit &circuit,const ComponentItemManager &itemManager)
{
    QPen wirePen(QColor(31, 41, 55), 2.2);
    for(auto comp:circuit.getComponents())
    {
        auto comp1=dynamic_cast<Voltmeter *>(comp);
        if(comp1==nullptr)
            continue;
        int targetId = comp1->getTargetComponentId();
        if(targetId==-1)
            continue ;
        auto meter = itemManager.findItemByComponentId(comp->getId());
        auto target = itemManager.findItemByComponentId(targetId);
        QPainterPath path(meter->leftPointScenePos());
        path.lineTo(target->leftPointScenePos());
        QPainterPath path1(meter->rightPointScenePos());
        path1.lineTo(target->rightPointScenePos());
        auto *wire = scene->addPath(path1,wirePen);
        wire->setZValue(-1);
        auto *wire1 = scene->addPath(path,wirePen);
        wire1->setZValue(-1);
        wireItems.push_back(wire);
        wireItems.push_back(wire1);
    }
}

void WireManager::drawSeriesWires(const CircuitLayout &layout)
{
    const auto &items = layout.orderedItems;

    if (scene == nullptr || items.empty())
        return;

    QPen wirePen(QColor(31, 41, 55), 2.2);
    wirePen.setCapStyle(Qt::RoundCap);
    wirePen.setJoinStyle(Qt::RoundJoin);

    for (std::size_t i = 0; i < items.size(); ++i)
    {
        const auto &current = items[i];
        const auto &next = items[(i + 1) % items.size()];

        bool currentLeftToRight = (current.rowIndex % 2 == 0);
        bool nextLeftToRight = (next.rowIndex % 2 == 0);
        //辅助判断连接顺序
        bool closingWire = (i == items.size() - 1);

        QPointF start = currentLeftToRight ? current.rightPoint : current.leftPoint;
        QPointF end = nextLeftToRight ? next.leftPoint : next.rightPoint;
        //判断连接点究竟是哪一个

        QPainterPath path(start);
        //判断连线路径模式
        if (closingWire)
        {
            if (currentLeftToRight)
            {
                //最后一行向右结束，需要从底部绕回第一行左侧
                path.lineTo(layout.rightRouteX, start.y());
                path.lineTo(layout.rightRouteX, layout.bottomRouteY);
                path.lineTo(layout.closingLeftX, layout.bottomRouteY);
                path.lineTo(layout.closingLeftX, end.y());
                //以上均为设置折线路径
            }
            else
            {
                //最后一行向左结束，直接沿左侧返回
                path.lineTo(layout.closingLeftX, start.y());
                path.lineTo(layout.closingLeftX, end.y());
            }//以上对最后一次进行特殊处理--->防止出现多行重叠问题虽然不太美观()
        }
        else if (current.rowIndex == next.rowIndex)
        {
            //同一行，在两个元器件中间进行直角转折
            qreal middleX = (start.x() + end.x()) / 2.0;

            path.lineTo(middleX, start.y());
            path.lineTo(middleX, end.y());
        }
        else
        {
            //从当前行末端转入下一行
            qreal routeX = currentLeftToRight ? layout.rightRouteX : layout.leftRouteX;

            path.lineTo(routeX, start.y());
            path.lineTo(routeX, end.y());
        }

        path.lineTo(end);//不做特殊处理直接连回end点

        auto *wire = scene->addPath(path, wirePen);
        wire->setZValue(-1);//覆盖层级设置导线为元器件下方
        wireItems.push_back(wire);
    }
}