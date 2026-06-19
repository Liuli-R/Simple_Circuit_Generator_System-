#ifndef WIREMANAGER_H
#define WIREMANAGER_H

#include <vector>

class Circuit;
class ComponentItemManager;
class QGraphicsLineItem;
class QGraphicsScene;

class WireManager
{
public:
    explicit WireManager(QGraphicsScene *scene);

    void clearWires();
    void drawSeriesWires(const Circuit &circuit, const ComponentItemManager &itemManager);

private:
    QGraphicsScene *scene = nullptr;
    std::vector<QGraphicsLineItem *> wireItems;
};

#endif // WIREMANAGER_H
