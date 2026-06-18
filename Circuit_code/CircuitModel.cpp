#include "CircuitModel.h"
#include "Ammeter.h"
#include "Battery.h"
#include "Bulb.h"
#include "Voltmeter.h"

/*const std::vector<Component*>& CircuitModel::currentComponents() const {
    return orderedComponents.empty() ? components : orderedComponents;
}

int CircuitModel::Cconstruct(Component* comp) {
    if (comp == nullptr) return static_cast<int>(components.size());
    components.push_back(comp);
    return static_cast<int>(components.size());
}

void CircuitModel::connection() {
    orderedComponents.clear();

    // 保留原逻辑：先把电源放到排序容器前面，其他元件顺序不变。
    for (auto comp : components) {
        if (comp != nullptr && comp->getTypeName() == "battery") {
            orderedComponents.push_back(comp);
        }
    }
    for (auto comp : components) {
        if (comp != nullptr && comp->getTypeName() != "battery") {
            orderedComponents.push_back(comp);
        }
    }

    int activeCount = 0;
    // 电压表视为测量支路，不计入主串联回路元件数量。
    for (auto comp : orderedComponents) {
        if (comp != nullptr && comp->getTypeName() != "voltmeter") {
            activeCount++;
        }
    }

    if (orderedComponents.empty() || activeCount == 0) return;

    int point = 1;
    for (auto comp : orderedComponents) {
        if (comp == nullptr) continue;

        // 电压表只按当前位置临时接到相邻节点，不推进主回路节点编号。
        if (comp->getTypeName() == "voltmeter") {
            comp->setLeftNode(point);
            comp->setRightNode(point + 1);
        } else {
            comp->setLeftNode(point);
            point++;
            comp->setRightNode(point > activeCount ? 1 : point);
        }
    }
}

bool CircuitModel::isClosedLoop() const {
    bool hasActiveComponent = false;
    for (auto comp : currentComponents()) {
        // 电压表不作为主回路闭合的必要元件。
        if (comp == nullptr || comp->getTypeName() == "voltmeter") {
            continue;
        }
        hasActiveComponent = true;
        if (comp->getLeftNodeId() == -1 || comp->getRightNodeId() == -1) {
            return false;
        }
    }
    return hasActiveComponent;
}

std::string CircuitModel::getvc() const {
    // 简化判断：查找与电压表左节点相同的元件，返回其类型名。
    for (auto meter : currentComponents()) {
        if (meter == nullptr || meter->getTypeName() != "voltmeter") {
            continue;
        }

        for (auto comp : currentComponents()) {
            if (comp == nullptr || comp == meter || comp->getTypeName() == "voltmeter") {
                continue;
            }
            if (meter->getLeftNodeId() == comp->getLeftNodeId()) {
                return comp->getTypeName();
            }
        }
    }
    return "";
}

double CircuitModel::getR() const {
    double sum = 0.0;
    for (auto comp : currentComponents()) {
        // 电压表理想情况下不参与总电阻计算。
        if (comp != nullptr && comp->getTypeName() != "voltmeter") {
            sum += comp->getResistance();
        }
    }
    return sum;
}

double CircuitModel::getV() const {
    double sum = 0.0;
    for (auto comp : currentComponents()) {
        Battery* battery = dynamic_cast<Battery*>(comp);
        if (battery != nullptr) {
            sum += battery->getVoltage();
        }
    }
    return sum;
}

double CircuitModel::getU() const {
    return getV();
}

double CircuitModel::getRV() const {
    std::string measuredType = getvc();
    if (measuredType.empty()) return -1.0;

    for (auto comp : currentComponents()) {
        if (comp != nullptr && comp->getTypeName() == measuredType) {
            return comp->getResistance();
        }
    }
    return -1.0;
}

void CircuitModel::setI(double A) {
    for (auto comp : currentComponents()) {
        // 基类没有 setI，确认是电流表后再设置读数。
        Ammeter* ammeter = dynamic_cast<Ammeter*>(comp);
        if (ammeter != nullptr) {
            ammeter->setI(A);
        }
    }
}

void CircuitModel::setlight(bool lit) {
    for (auto comp : currentComponents()) {
        // 灯泡只关心亮灭状态，不保存电流值。
        Bulb* bulb = dynamic_cast<Bulb*>(comp);
        if (bulb != nullptr) {
            bulb->setLit(lit);
        }
    }
}

void CircuitModel::setU(double V) {
    for (auto comp : currentComponents()) {
        // 基类没有 setU，确认是电压表后再设置读数。
        Voltmeter* voltmeter = dynamic_cast<Voltmeter*>(comp);
        if (voltmeter != nullptr) {
            voltmeter->setU(V);
        }
    }
}*/
