#include "Circuit.h"

#include "Circuit_code/Battery.h"
#include "Circuit_code/Component.h"
#include "Circuit_code/Node.h"
#include "Circuit_code/Ammeter.h"
#include "Circuit_code/Voltmeter.h"

#include <cstddef>
#include <map>
#include <vector>

Circuit::Circuit()
{
}

Circuit::~Circuit()
{
    clearCircuit();
}

void Circuit::clearCircuit()
{
    for (auto comp : components)
        delete comp;
    components.clear();
    for (auto node : nodes)
        delete node;
    nodes.clear();
    nextNodeId = 1;//重新计数
}

Component *Circuit::addComponent(Component *comp)
{
    if (comp == nullptr)
        return nullptr;
    components.push_back(comp);
    return comp;
}

int Circuit::addNode(int x, int y)
{
    Node *node = new Node(nextNodeId++, x, y);
    nodes.push_back(node);
    return node->getId();
}

void Circuit::connectLeft(Component *comp, int nodeId)
{
    if (comp == nullptr)
        return;
    comp->setLeftNode(nodeId);
}

void Circuit::connectRight(Component *comp, int nodeId)
{
    if (comp == nullptr)
        return;
    comp->setRightNode(nodeId);
}

const std::vector<Component *> Circuit::getMainLoopComponents() const
{
    std::vector<Component *> result;
    // 电压表不参与主回路导通判断，这里只检查主串联回路元件
    for (auto comp : components) {
        if (comp != nullptr && comp->getTypeName() != "voltmeter") {
            result.push_back(comp);
        }
    }

    return result;
}

const std::vector<Component *> &Circuit::getComponents() const
{
    return components;
}

const std::vector<Node *> &Circuit::getNodes() const
{
    return nodes;
}

bool Circuit::hasBattery() const
{
    for (auto comp : components)
    {
        auto comp1 = dynamic_cast<Battery *>(comp);
        if (comp1 != nullptr)
            return true;
    }
    return false;
}

bool Circuit::hasAmmeter() const
{
    for (auto comp : components)
    {
        auto comp1 = dynamic_cast<Ammeter *>(comp);
        if (comp1 != nullptr)
            return true;
    }
    return false;
}

bool Circuit::hasVoltmeter() const
{
    for (auto comp : components)
    {
        auto comp1 = dynamic_cast<Voltmeter *>(comp);
        if (comp1 != nullptr)
            return true;
    }
    return false;
}

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

bool Circuit::buildClosedLoop()
{
    //连通排序容器与旧版CircuitModel的orderedComponents相似
    std::vector<Component *> activeComponents;

    // 自动构造闭环时同样排除电压表，只处理主串联回路。
    for (auto comp : components) {
        if (comp && comp->getTypeName() != "voltmeter") {
            activeComponents.push_back(comp);
        }
    }

    if (activeComponents.empty() || nodes.empty())
        return false;
    if (activeComponents.size() != nodes.size())
        return false;

    for (std::size_t i = 0; i < activeComponents.size(); i++)
    {// 按添加顺序连接：第 i 个元件连接第 i 个节点和下一个节点，最后连回第一个节点。
        int leftNodeId = nodes[i]->getId();
        int rightNodeId = nodes[(i + 1) % nodes.size()]->getId();
        connectLeft(activeComponents[i], leftNodeId);
        connectRight(activeComponents[i], rightNodeId);
    }

    return true;
}

Component *Circuit::findComponentById(int id) const
{
    for (auto *comp : components)
    {
        if (comp != nullptr && comp->getId() == id)
        {
            return comp;
        }
    }
    return nullptr;
}

int Circuit::getComponentCount() const
{
    return static_cast<int>(components.size());
}

void Circuit::connectVoltmeterTo(Voltmeter *meter, Component *target)
{
    if (!meter || !target)
        return;

    connectLeft(meter,target->getLeftNodeId());
    connectRight(meter,target->getRightNodeId());
    meter->setTargetComponentId(target->getId());
}//人为设置想让电压表测哪一个元器件,Qt端设计发现原先缺失对节点的固定判断
