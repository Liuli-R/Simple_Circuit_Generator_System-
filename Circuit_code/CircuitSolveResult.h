#ifndef CIRCUITSOLVERESULT_H
#define CIRCUITSOLVERESULT_H
//此结构体的设计初衷和目的是为了将每次计算结果的"快照"呈现出来
//可以称为 求解器对应的结构存储器
#include <vector>

enum class CircuitRunState
{
    NotRun,
    Open,
    MissingBattery,
    InvalidResistance,
    Running
};//枚举了五种电路运行的状态

struct VoltmeterSolveResult
{
    int voltmeterId = -1;
    int targetComponentId = -1;
    bool hasTarget = false;
    double reading = 0.0;
};//存储电压表记录的多种数据 多种数据就用结构体来存储->不错的思路

struct CircuitSolveResult//默认设置，默认构造
{
    CircuitRunState state = CircuitRunState::NotRun;//默认不运行

    double totalVoltage = 0.0;
    double totalResistance = 0.0;
    double current = 0.0;
    double voltmeterReading = 0.0;

    bool hasAmmeter = false;
    bool hasVoltmeter = false;
    bool voltmeterHasTarget = false;

    std::vector<VoltmeterSolveResult> voltmeters;
    //设计初衷 服务于记录可能存在多个电压表同时体现测不同元器件电压
};

#endif // CIRCUITSOLVERESULT_H
