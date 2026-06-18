#include "CircuitSolver.h"
#include <iostream>

CircuitModel& CircuitSolver::getCircuitModel() {
    return circuit;
}

const CircuitModel& CircuitSolver::getCircuitModel() const {
    return circuit;
}

void CircuitSolver::show() {
    if (!circuit.isClosedLoop()) {
        std::cout << "Cannot calculate: circuit is not closed." << std::endl;
        return;
    }

    double totalVoltage = circuit.getV();
    double totalResistance = circuit.getR();
    if (totalResistance == 0.0) {
        std::cout << "Cannot calculate: total resistance is zero." << std::endl;
        return;
    }

    // 简单串联模型：I = U / R。
    double current = totalVoltage / totalResistance;
    circuit.setI(current);
    circuit.setlight(true);

    // 如果存在可识别的电压表测量对象，则按 U = I * R 设置读数。
    double measuredResistance = circuit.getRV();
    if (measuredResistance >= 0.0) {
        double measuredVoltage = current * measuredResistance;
        circuit.setU(measuredVoltage);
    }
}
