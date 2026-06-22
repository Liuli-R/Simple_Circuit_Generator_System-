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