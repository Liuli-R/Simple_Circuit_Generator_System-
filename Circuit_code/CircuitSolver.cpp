#include "CircuitSolver.h"

#include "Battery.h"
#include "Ammeter.h"
#include "Voltmeter.h"
#include "Bulb.h"
#include "Circuit.h"
#include "Component.h"
#include "CircuitSolveResult.h"

double CircuitSolver::getTotalResistance(const Circuit &circuit) const
{
    double sum = 0.0;
    for (auto comp : circuit.getComponents()) {
        //auto工程好处不用自己进行复杂类型判断 这样写避免多余一次内存开销
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

    for (auto *component : targetedCircuit.getComponents())
    {
        auto *meter = dynamic_cast<Voltmeter *>(component);

        if (meter == nullptr)
            continue;

        auto *target = targetedCircuit.findComponentById(meter->getTargetComponentId());

        VoltmeterSolveResult meterResult;
        meterResult.voltmeterId = meter->getId();

        if (target != nullptr)
        {
            meterResult.hasTarget = true;
            meterResult.targetComponentId = target->getId();
            meterResult.reading = target->getResistance() * result.current;
        }

        meter->setU(meterResult.reading);
        result.voltmeters.push_back(meterResult);
    }//思路优化->由单一电压表记录提升为支持多个电压表记录

    result.state = CircuitRunState::Running;
    return result;
}
