#ifndef COMPONENTITEMMANAGER_H
#define COMPONENTITEMMANAGER_H

#include "Graphics/items/ComponentItem.h"
#include <QGraphicsScene>
#include "Circuit_code/Component.h"
#include <vector>

class ComponentItemManager
{
    public:
        ComponentItemManager(QGraphicsScene *scene);

        ComponentItem* addComponentItem(Component *component);
        ComponentItem* createItem(Component *component) const;
        ComponentItem* findItemByComponentId(int componentId) const;

        void layoutItems();
        //后期预备删除or撤回元器件后，自动整理画布元器件按排列的函数
        void clearAll();
        int itemCount() const;

    private:
        QPointF defaultPositionForIndex(int index) const;
        //锚定图上生成元器件的默认位置

        QGraphicsScene *scene = nullptr;
        std::vector<ComponentItem*> items;
};

#endif // COMPONENTITEMMANAGER_H
