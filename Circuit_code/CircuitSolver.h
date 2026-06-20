#pragma once

#include <vector>
#include "CircuitSolveResult.h"

class Circuit;
class Component;

class CircuitSolver
{
public:
    //执行简单的串联电路计算
    //变化从bool变为返回结果类型就是将多种计算结果保存到一个结构体中
    CircuitSolveResult solve(Circuit &circuit, bool switchesClosed);

private:
    Circuit *circuit = nullptr;


    //获取排序完成元器件容器为了辅助下面的计算逻辑设计
    std::vector<Component *> getOrderedComponents() const;
    // 获取电压表当前粗略测量到的元件指针。
    Component *findVoltmeterTarget() const;
    // getR/getV/getU 用于简单串联电路的基础计算。
    double getTotalResistance() const;
    double getTotalVoltage() const;
    double getMeasuredResistance() const;

    void setAmmeters(double current);
    void setBulbs(bool lit);
    void setVoltmeters(double voltage);
};
