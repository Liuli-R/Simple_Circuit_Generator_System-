#ifndef COMPONENTITEMMANAGER_H
#define COMPONENTITEMMANAGER_H

#include "Graphics/ComponentItem.h"
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
        void clearAll();
        int itemCount() const;

    private:
        QPointF defaultPositionForIndex(int index) const;

        QGraphicsScene *scene = nullptr;
        std::vector<ComponentItem*> items;
};

#endif // COMPONENTITEMMANAGER_H
