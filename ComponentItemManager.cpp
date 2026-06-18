#include "ComponentItemManager.h"

#include "Graphics/BatteryItem.h"
#include "Graphics/BulbItem.h"
#include "Graphics/ResistorItem.h"
#include "Graphics/SwitchItem.h"
#include "Graphics/AmmeterItem.h"
#include "Graphics/VoltmeterItem.h"

ComponentItemManager::ComponentItemManager(QGraphicsScene *scene)
    : scene(scene)
{
}

ComponentItem* ComponentItemManager::createItem(Component *component) const
{
    const int id = component->getId();
    const std::string type = component->getTypeName();

    if (type == "battery") {
        return new BatteryItem(id);
    }
    if (type == "bulb") {
        return new BulbItem(id);
    }
    if (type == "resistor") {
        return new ResistorItem(id);
    }
    if (type == "switch") {
        return new SwitchItem(id);
    }
    if (type == "ammeter") {
        return new AmmeterItem(id);
    }
    if (type == "voltmeter") {
        return new VoltmeterItem(id);
    }

    return nullptr;
}

ComponentItem* ComponentItemManager::addComponentItem(Component *component)
{
    if (scene == nullptr || component == nullptr) {
        return nullptr;
    }

    ComponentItem *item = createItem(component);
    if (item == nullptr) {
        return nullptr;
    }

    item->setPos(defaultPositionForIndex(static_cast<int>(items.size())));
    scene->addItem(item);
    items.push_back(item);

    return item;
}

ComponentItem* ComponentItemManager::findItemByComponentId(int componentId) const
{
    for (auto *item : items) {
        if (item != nullptr && item->getComponentId() == componentId) {
            return item;
        }
    }

    return nullptr;
}

void ComponentItemManager::layoutItems()
{
    for (int i = 0; i < static_cast<int>(items.size()); ++i) {
        if (items[i] != nullptr) {
            items[i]->setPos(defaultPositionForIndex(i));
        }
    }
}

QPointF ComponentItemManager::defaultPositionForIndex(int index) const
{
    const int columns = 5;
    const int spacingX = 145;
    const int spacingY = 120;
    const int startX = 110;
    const int startY = 110;

    return QPointF(
        startX + (index % columns) * spacingX,
        startY + (index / columns) * spacingY
        );
}

void ComponentItemManager::clearAll()
{
    if (scene != nullptr) {
        scene->clear();
    }
    items.clear();
}

int ComponentItemManager::itemCount() const
{
    return static_cast<int>(items.size());
}