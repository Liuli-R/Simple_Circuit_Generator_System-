#include "Circuit.h"
#include <cstddef>
#include <map>
#include <vector>

Circuit::Circuit() {}

Circuit::~Circuit() {
    for (auto comp : components) delete comp;
    for (auto node : nodes) delete node;
    nextNodeId=1;//重新计数
}

Component* Circuit::addComponent(Component* comp) {
    if (comp == nullptr) return nullptr;
    components.push_back(comp);
    return comp;
}

int Circuit::addNode(int x, int y) {
    Node* node = new Node(nextNodeId++, x, y);
    nodes.push_back(node);
    return node->getId();
}

void Circuit::connectLeft(Component* comp, int nodeId) {
    if (comp == nullptr) return;
    comp->setLeftNode(nodeId);
}

void Circuit::connectRight(Component* comp, int nodeId) {
    if (comp == nullptr) return;
    comp->setRightNode(nodeId);
}

const std::vector<Component*>& Circuit::getComponents() const {
    return components;
}

const std::vector<Node*>& Circuit::getNodes() const {
    return nodes;
}

bool Circuit::isClosedLoop() const {
    std::vector<Component*> activeComponents;

    // 电压表不参与主回路导通判断，这里只检查主串联回路元件。
    for (auto comp : components) {
        if (comp != nullptr && comp->getTypeName() != "voltmeter") {
            activeComponents.push_back(comp);
        }
    }

    if (activeComponents.empty()) return false;

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
    std::map<int, Component*> leftMap;
    for (auto comp : activeComponents) {
        int leftNode = comp->getLeftNodeId();
        if (leftMap.count(leftNode) > 0) {
            return false;
        }
        leftMap[leftNode] = comp;
    }

    int startNodeId = activeComponents[0]->getLeftNodeId();
    int curNode = startNodeId;
    std::vector<Component*> ordered;

    while (leftMap.count(curNode) > 0 && ordered.size() < activeComponents.size()) {
        Component* comp = leftMap[curNode];
        ordered.push_back(comp);
        curNode = comp->getRightNodeId();
    }

    // 走完所有元件后回到起点，说明形成简单闭合回路。
    return ordered.size() == activeComponents.size() && curNode == startNodeId;
}

bool Circuit::buildClosedLoop() {
    //连通排序容器与旧版CircuitModel的orderedComponents相似
    std::vector<Component*> activeComponents;

    //先把电源放到排序容器前面，其他元件顺序不变
    for (auto comp : components) {
        if (comp && comp->getTypeName() == "battery") {
            activeComponents.push_back(comp);
        }
    }
    // 自动构造闭环时同样排除电压表和电源，只处理主串联回路。
    for (auto comp : components) {
        if (comp &&comp->getTypeName() != "battery" &&comp->getTypeName() != "voltmeter") {
            activeComponents.push_back(comp);
        }
    }

    if (activeComponents.empty() || nodes.empty()) return false;
    if (activeComponents.size() != nodes.size()) return false;

    // 按添加顺序连接：第 i 个元件连接第 i 个节点和下一个节点，最后连回第一个节点。
    for (std::size_t i = 0; i < activeComponents.size(); i++) {
        int leftNodeId = nodes[i]->getId();
        int rightNodeId = nodes[(i + 1) % nodes.size()]->getId();
        connectLeft(activeComponents[i], leftNodeId);
        connectRight(activeComponents[i], rightNodeId);
    }

    return true;
}

int Circuit::getComponentCount() const
{
    return static_cast<int>(components.size());
}
