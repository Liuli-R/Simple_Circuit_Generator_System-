#include "CircuitSolver.h"

#include "Battery.h"
#include "Ammeter.h"
#include "Voltmeter.h"
#include "Bulb.h"
#include "Circuit.h"
#include "Component.h"
#include "CircuitSolveResult.h"

#include <vector>

std::vector<Component *> CircuitSolver::getOrderedComponents() const
{
    //连通排序容器与旧版CircuitModel的orderedComponents相似
    std::vector<Component *> orderedComponents;

    //先把电源放到排序容器前面，其他元件顺序不变
    for (auto comp : circuit->getComponents()) {
        if (comp && comp->getTypeName() == "battery") {
            orderedComponents.push_back(comp);
        }
    }
    for (auto comp : circuit->getComponents()) {
        if (comp && comp->getTypeName() != "battery") {
            orderedComponents.push_back(comp);
        }
    }
    return orderedComponents;
}

Component *CircuitSolver::findVoltmeterTarget() const
{
    auto ordered = getOrderedComponents();
    //auto工程好处不用自己进行复杂类型判断 这样写避免多余一次内存开销
    // 简化判断：查找与电压表左节点相同的元件，返回其类型名。
    for (auto meter : ordered) {
        if (meter == nullptr || meter->getTypeName() != "voltmeter") {
            continue;
        }

        for (auto comp : ordered) {
            //预留优化空间:电压表测多个元器件功能
            if (comp == nullptr || comp == meter || comp->getTypeName() == "voltmeter") {
                continue;
            }
            if (meter->getLeftNodeId() == comp->getLeftNodeId()) {
                return comp;
            }
        }
    }
    return nullptr;
}

double CircuitSolver::getTotalResistance() const
{
    double sum = 0.0;
    for (auto comp : getOrderedComponents()) {
        // 电压表理想情况下不参与总电阻计算。
        if (comp != nullptr && comp->getTypeName() != "voltmeter" && comp->getTypeName() != "battery")
        {
            sum += comp->getResistance();
        }
    }
    return sum;
}

double CircuitSolver::getTotalVoltage() const
{
    double sum = 0.0;
    for (auto comp : getOrderedComponents()) {
        Battery *battery = dynamic_cast<Battery *>(comp);
        if (battery != nullptr) {
            sum += battery->getVoltage();
        }
    }
    return sum;
}

double CircuitSolver::getMeasuredResistance() const
{
    auto comp = findVoltmeterTarget();
    if (!comp)
        return -1.0;
    return comp->getResistance();
}

//优化内存存储空间
void CircuitSolver::setAmmeters(double current)
{
    for (auto comp : circuit->getComponents()) {
        // 基类没有 setI，确认是电流表后再设置读数。
        Ammeter *ammeter = dynamic_cast<Ammeter *>(comp);
        if (ammeter != nullptr) {
            ammeter->setI(current);
        }
    }
}

void CircuitSolver::setBulbs(bool lit)
{
    for (auto comp : circuit->getComponents()) {
        // 灯泡只关心亮灭状态，不保存电流值。
        Bulb *bulb = dynamic_cast<Bulb *>(comp);
        if (bulb != nullptr) {
            bulb->setLit(lit);
        }
    }
}

void CircuitSolver::setVoltmeters(double voltage)
{
    for (auto comp : circuit->getComponents()) {
        // 基类没有 setU，确认是电压表后再设置读数。
        Voltmeter *voltmeter = dynamic_cast<Voltmeter *>(comp);
        if (voltmeter != nullptr) {
            voltmeter->setU(voltage);
        }
    }
}

CircuitSolveResult CircuitSolver::solve(Circuit &targetedCircuit, bool switchesClosed)
{
    //非法条件都会置空本类的电路指针保证及时断开重新计算
    circuit = &targetedCircuit;
    CircuitSolveResult result;

    result.hasAmmeter = circuit->hasAmmeter();
    result.hasVoltmeter = circuit->hasVoltmeter();
    result.totalVoltage = getTotalVoltage();
    result.totalResistance = getTotalResistance();
    double measuredResistance = getMeasuredResistance();
    result.voltmeterHasTarget = measuredResistance >= 0.0;

    if (!switchesClosed || !circuit->isClosedLoop())
    {
        setBulbs(false);
        setAmmeters(0.0);
        setVoltmeters(0.0);
        circuit = nullptr;

        result.state = CircuitRunState::Open;
        return result;
    }

    if (!circuit->hasBattery())
    {
        setBulbs(false);
        setAmmeters(0.0);
        setVoltmeters(0.0);
        circuit = nullptr;

        result.state = CircuitRunState::MissingBattery;
        return result;
    }

    if (result.totalResistance <= 0.0)
    {
        setBulbs(false);
        setAmmeters(0.0);
        setVoltmeters(0.0);
        circuit = nullptr;

        result.state = CircuitRunState::InvalidResistance;
        return result;
    }

    result.current =result.totalVoltage / result.totalResistance;
    setAmmeters(result.current);
    setBulbs(true);

    if(result.voltmeterHasTarget)
        result.voltmeterReading=measuredResistance * result.current;
    setVoltmeters(result.voltmeterReading);

    result.state = CircuitRunState::Running;

    circuit=nullptr;
    return result;

}
