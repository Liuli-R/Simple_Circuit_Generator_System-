#include "Circuit.h"
#include "Circuit_code/Component.h"
#include "Circuit_code/Node.h"
#include "Circuit_code/Voltmeter.h"

#include <map>
#include <vector>
//采用cpp特性分离编译->进行拆分原先Circuit的cpp代码
bool Circuit::isClosedLoop() const
{
    std::vector<Component *> activeComponents = getMainLoopComponents();

    if (activeComponents.empty())
        return false;

    // 任一元件左右端口未连接节点，都不能构成闭合回路。
    for (auto comp : activeComponents) {
        if (comp->getLeftNodeId() == -1 || comp->getRightNodeId() == -1) {
            return false;
        }
    }

    if (activeComponents.size() == 1) {
        return activeComponents[0]->getLeftNodeId() == activeComponents[0]->getRightNodeId();
    }

    // 用“左节点 -> 元件”的映射沿着右节点往后走，适合简单串联结构。
    std::map<int, Component *> leftMap;
    for (auto comp : activeComponents) {
        int leftNode = comp->getLeftNodeId();
        if (leftMap.count(leftNode) > 0) {
            return false;
        }
        leftMap[leftNode] = comp;
    }

    int startNodeId = activeComponents[0]->getLeftNodeId();
    int curNode = startNodeId;
    std::vector<Component *> ordered;

    while (leftMap.count(curNode) > 0 && ordered.size() < activeComponents.size()) {
        Component *comp = leftMap[curNode];
        ordered.push_back(comp);
        curNode = comp->getRightNodeId();
    }

    // 走完所有元件后回到起点，说明形成简单闭合回路。
    return ordered.size() == activeComponents.size() && curNode == startNodeId;
}

bool Circuit::buildClosedLoop(const std::vector<int> orderedIds)
{//边界处理防止电压表混入
    if (orderedIds.empty() || nodes.empty())
        return false;
    if (orderedIds.size() != nodes.size())
        return false;

    for (std::size_t i = 0; i < orderedIds.size(); i++)
    {//按最终画布上元器件按排布顺序->进行连接端点判断
        auto comp = findComponentById(orderedIds[i]);
        if (comp == nullptr  || comp->getTypeName() == "voltmeter")
            return false;
        connectLeft(comp,nodes[i]->getId());
        connectRight(comp,nodes[(i+1)%nodes.size()]->getId());
    }

    for (auto *component : components)
    {
        auto *meter = dynamic_cast<Voltmeter *>(component);

        if (meter == nullptr)
            continue;

        int targetId = meter->getTargetComponentId();

        if (targetId < 0)
            continue;

        Component *target = findComponentById(targetId);

        if (target == nullptr ||
            target->getTypeName() == "voltmeter")
            continue;

        connectVoltmeterTo(meter, target);
    }
    return true;
}

void Circuit::connectVoltmeterTo(Voltmeter *meter, Component *target)
{
    if (!meter || !target)
        return;

    connectLeft(meter,target->getLeftNodeId());
    connectRight(meter,target->getRightNodeId());
    meter->setTargetComponentId(target->getId());
}//人为设置想让电压表测哪一个元器件,Qt端设计发现原先缺失对节点的固定判断
