#pragma once

#include "CircuitSolveResult.h"

class Circuit;
class Component;

class CircuitSolver //求解器
{
public:
    //执行简单的串联电路计算
    //变化从bool变为返回结果类型就是将多种计算结果保存到一个结构体中
    void resetOutputs(Circuit &circuit);//重置清除结果
    CircuitSolveResult solve(Circuit &circuit, bool switchesClosed);

private:
    //以下是用于简单串联电路的基础计算 计算总电阻 计算总电压->进而有电流
    double getTotalResistance(const Circuit &circuit) const;
    double getTotalVoltage(const Circuit &circuit) const;

    void setAmmeters(double current,Circuit &circuit);
    void setBulbs(bool lit,Circuit &circuit);
    void setVoltmeters(double voltage,Circuit &circuit);
};
