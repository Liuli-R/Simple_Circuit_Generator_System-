#include "ComponentItemManager.h"

#include "Circuit_code/Component.h"
#include "Graphics/items/BatteryItem.h"
#include "Graphics/items/BulbItem.h"
#include "Graphics/items/ComponentItem.h"
#include "Graphics/items/ResistorItem.h"
#include "Graphics/items/SwitchItem.h"
#include "Graphics/items/AmmeterItem.h"
#include "Graphics/items/VoltmeterItem.h"

#include <QGraphicsScene>
#include <QPointF>

#include <string>

ComponentItemManager::ComponentItemManager(QGraphicsScene *scene)
    : scene(scene)
{
}

ComponentItem *ComponentItemManager::createItem(Component *component) const
{
    const int id = component->getId();
    const std::string type = component->getTypeName();

    if (type == "battery")
    {
        return new BatteryItem(id);
    }
    if (type == "bulb")
    {
        return new BulbItem(id);
    }
    if (type == "resistor")
    {
        return new ResistorItem(id);
    }
    if (type == "switch")
    {
        return new SwitchItem(id);
    }
    if (type == "ammeter")
    {
        return new AmmeterItem(id);
    }
    if (type == "voltmeter")
    {
        return new VoltmeterItem(id);
    }

    return nullptr;
}

ComponentItem *ComponentItemManager::addComponentItem(Component *component)
{
    if (scene == nullptr || component == nullptr)
    {
        return nullptr;
    }

    ComponentItem *item = createItem(component);
    if (item == nullptr)
    {
        return nullptr;
    }
    //setPos这个函数是重载于QGraphicsItem中的函数
    item->setPos(defaultPositionForIndex(static_cast<int>(items.size())));
    scene->addItem(item);
    items.push_back(item);

    return item;
}

ComponentItem *ComponentItemManager::findItemByComponentId(int componentId) const
{
    for (auto *item : items)
    {
        if (item != nullptr && item->getComponentId() == componentId)
        {
            return item;
        }
    }

    return nullptr;
}

void ComponentItemManager::layoutItems()
{
    for (int i = 0; i < static_cast<int>(items.size()); ++i)
    {
        if (items[i] != nullptr)
        {
            items[i]->setPos(defaultPositionForIndex(i));
        }
    }
}

QPointF ComponentItemManager::defaultPositionForIndex(int index) const
{
    const int columns = 6;
    const int spacingX = 145;
    const int spacingY = 120;
    const int startX = 110;
    const int startY = 110;

    return QPointF(
        startX + (index % columns) * spacingX,
        startY + (index / columns) * spacingY
    );
}//元器件整体位置布局

void ComponentItemManager::clearAll()
{
    if (scene != nullptr)
    {
        scene->clear();
    }
    items.clear();
    //清除画布上的所有条目对象，以及清空容器
}

int ComponentItemManager::itemCount() const
{
    return static_cast<int>(items.size());
    //返回容器内数量计数
}
