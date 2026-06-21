#include "CircuitSolver.h"

#include "Battery.h"
#include "Ammeter.h"
#include "Voltmeter.h"
#include "Bulb.h"
#include "Circuit.h"
#include "Component.h"
#include "CircuitSolveResult.h"

Component *CircuitSolver::findVoltmeterTarget(const Circuit &circuit) const
{
    auto ordered = circuit.getComponents();
    //auto工程好处不用自己进行复杂类型判断 这样写避免多余一次内存开销
    // 简化判断：查找与电压表左节点相同的元件，返回其类型名。
    for (auto meter : ordered)
    {
        if (meter == nullptr || meter->getTypeName() != "voltmeter")
            continue;

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

double CircuitSolver::getTotalResistance(const Circuit &circuit) const
{
    double sum = 0.0;
    for (auto comp : circuit.getComponents()) {
        // 电压表理想情况下不参与总电阻计算。
        if (comp != nullptr && comp->getTypeName() != "voltmeter" && comp->getTypeName() != "battery")
        {
            sum += comp->getResistance();
        }
    }
    return sum;
}

double CircuitSolver::getTotalVoltage(const Circuit &circuit) const
{
    double sum = 0.0;
    for (auto comp : circuit.getComponents()) {
        Battery *battery = dynamic_cast<Battery *>(comp);
        if (battery != nullptr) {
            sum += battery->getVoltage();
        }
    }
    return sum;
}

double CircuitSolver::getMeasuredResistance(const Circuit &circuit) const
{
    auto comp = findVoltmeterTarget(circuit);
    if (!comp)
        return -1.0;
    return comp->getResistance();
}

//优化内存存储空间
void CircuitSolver::setAmmeters(double current,Circuit &circuit)
{
    for (auto comp : circuit.getComponents()) {
        // 基类没有 setI，确认是电流表后再设置读数。
        Ammeter *ammeter = dynamic_cast<Ammeter *>(comp);
        if (ammeter != nullptr) {
            ammeter->setI(current);
        }
    }
}

void CircuitSolver::setBulbs(bool lit,Circuit &circuit)
{
    for (auto comp : circuit.getComponents()) {
        // 灯泡只关心亮灭状态，不保存电流值。
        Bulb *bulb = dynamic_cast<Bulb *>(comp);
        if (bulb != nullptr) {
            bulb->setLit(lit);
        }
    }
}

void CircuitSolver::setVoltmeters(double voltage,Circuit &circuit)
{
    for (auto comp : circuit.getComponents()) {
        // 基类没有 setU，确认是电压表后再设置读数。
        Voltmeter *voltmeter = dynamic_cast<Voltmeter *>(comp);
        if (voltmeter != nullptr) {
            voltmeter->setU(voltage);
        }
    }
}

void CircuitSolver::resetOutputs(Circuit &circuit)
{
    setBulbs(false,circuit);
    setAmmeters(0.0,circuit);
    setVoltmeters(0.0,circuit);
}//由于后边solve整体求解所用太多所以整合了一个简单的函数

CircuitSolveResult CircuitSolver::solve(Circuit &targetedCircuit, bool switchesClosed)
{
    CircuitSolveResult result;

    result.hasAmmeter = targetedCircuit.hasAmmeter();
    result.hasVoltmeter = targetedCircuit.hasVoltmeter();
    result.totalVoltage = getTotalVoltage(targetedCircuit);
    result.totalResistance = getTotalResistance(targetedCircuit);
    double measuredResistance = getMeasuredResistance(targetedCircuit);
    result.voltmeterHasTarget = measuredResistance >= 0.0;

    if (!switchesClosed || !targetedCircuit.isClosedLoop())
    {
        resetOutputs(targetedCircuit);
        result.state = CircuitRunState::Open;
        return result;
    }

    if (!targetedCircuit.hasBattery())
    {
        resetOutputs(targetedCircuit);
        result.state = CircuitRunState::MissingBattery;
        return result;
    }

    if (result.totalResistance <= 0.0)
    {
        resetOutputs(targetedCircuit);
        result.state = CircuitRunState::InvalidResistance;
        return result;
    }

    result.current =result.totalVoltage / result.totalResistance;
    setAmmeters(result.current,targetedCircuit);
    setBulbs(true,targetedCircuit);

    if(result.voltmeterHasTarget)
        result.voltmeterReading=measuredResistance * result.current;
    setVoltmeters(result.voltmeterReading,targetedCircuit);

    result.state = CircuitRunState::Running;
    return result;
}
