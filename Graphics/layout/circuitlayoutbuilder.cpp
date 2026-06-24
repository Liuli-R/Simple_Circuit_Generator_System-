#include "circuitlayoutbuilder.h"
#include "ComponentLayout.h"
#include "Graphics/layout/CircuitLayout.h"
#include "Circuit_code/Circuit.h"
#include "Graphics/items/ComponentItem.h"
#include "Graphics/manager/ComponentItemManager.h"
#include "Circuit_code/Component.h"

CircuitLayoutBuilder::CircuitLayoutBuilder() {}

CircuitLayout CircuitLayoutBuilder::build(const Circuit &circuit,const ComponentItemManager &manager,const QRectF &sceneRect)
{
    constexpr qreal rowTolerance = 80.0;
    constexpr qreal routeMargin = 30.0;
    constexpr qreal closingOffset = 18.0;
    //编译器常量->对于某一固定常数经常运用
    std::vector<ComponentLayout> items;

    for (auto *component : circuit.getMainLoopComponents())
    {
        auto *item = manager.findItemByComponentId(component->getId());
        //从排除电压表的元器件中对应的元器件图形
        if (item == nullptr)
            continue;

        ComponentLayout layout;
        layout.componentId = component->getId();
        layout.leftPoint = item->leftPointScenePos();
        layout.rightPoint = item->rightPointScenePos();
        layout.sceneBounds = item->mapRectToScene(item->boundingRect());
        //传回矩形在画布图形界面的矩形区域边界位置
        layout.centerY = layout.sceneBounds.center().y();

        items.push_back(layout);//存储每个元器件的位置
    }

    // 首先按照纵坐标排列，方便分行
    std::sort(items.begin(), items.end(),[](const ComponentLayout &a, const ComponentLayout &b)
    {
        return a.centerY < b.centerY;
    });

    std::vector<std::vector<ComponentLayout>> rows;
    //核心:
    for (const auto &item : items)
    {
        if (rows.empty() || qAbs(item.centerY - rows.back().front().centerY) > rowTolerance)
        //有点类似fabs那种浮点数比较 纵坐标差距大于一定范围进行新行的构建
            rows.push_back({item});//新建一行
        else
            rows.back().push_back(item);//在本行内增加一个元器件按
    }//这里呢 我们就有了一个小小限制核心是创建时最好只能按蛇形排列否则将会错行

    CircuitLayout result;
    QRectF totalBounds;
    //所有元器件的边界布局
    for (int row = 0; row < static_cast<int>(rows.size()); ++row)
    {
        auto &currentRow = rows[row];

        std::sort(currentRow.begin(), currentRow.end(),[](const auto &a, const auto &b)
        {
            return a.leftPoint.x() < b.leftPoint.x();
        });//按照思想，行内按照图形界面内x坐标排序

        if (row % 2 == 1)
            std::reverse(currentRow.begin(), currentRow.end());
        //按照思想，偶数奇数行排列顺序反转->这里设置奇数行反转

        for (auto &item : currentRow)
        {
            item.rowIndex = row;
            totalBounds = totalBounds.isNull()? item.sceneBounds: totalBounds.united(item.sceneBounds);
            //是空的就是第一个否则就是在原有基础上不断扩展的一个矩形检测
            result.orderedItems.push_back(item);
        }
    }//本质->二维数组的遍历

    result.leftRouteX =
        qMax(sceneRect.left() + 20, totalBounds.left() - routeMargin);
    result.rightRouteX =
        qMin(sceneRect.right() - 20, totalBounds.right() + routeMargin);
    result.bottomRouteY =
        qMin(sceneRect.bottom() - 20, totalBounds.bottom() + routeMargin);
    result.closingLeftX = result.leftRouteX - closingOffset;
    //边界处理
    return result;
}
