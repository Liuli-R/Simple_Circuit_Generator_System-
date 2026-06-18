#pragma once

#include "CircuitModel.h"

class CircuitSolver {
private:
    CircuitModel circuit;

public:
    // 暴露模型，方便外部先添加元件和建立连接。
    CircuitModel& getCircuitModel();
    const CircuitModel& getCircuitModel() const;

    // 执行简单串联电路计算。
    void show();
};
