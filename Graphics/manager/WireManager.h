#ifndef WIREMANAGER_H
#define WIREMANAGER_H

#include <vector>

class Circuit;
struct CircuitLayout;
class QGraphicsPathItem;
class QGraphicsScene;
class ComponentItemManager;

class WireManager
{
public:
    WireManager(QGraphicsScene *scene);

    void clearWires();
    void drawVoltmeterWires(const Circuit &circuit,const ComponentItemManager &itemManager);
    void drawSeriesWires(const CircuitLayout &layout);

private:
    QGraphicsScene *scene = nullptr;
    std::vector<QGraphicsPathItem *> wireItems;
    //大更新->优化导线显示为直角导线所以需要Path类
};

#endif // WIREMANAGER_H
