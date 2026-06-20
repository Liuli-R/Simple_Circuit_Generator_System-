#ifndef CIRCUITSOLVERESULT_H
#define CIRCUITSOLVERESULT_H
//此结构体的设计初衷和目的是为了将每次计算结果的"快照"呈现出来
enum class CircuitRunState
{
    NotRun,
    Open,
    MissingBattery,
    InvalidResistance,
    Running
};//枚举了五种电路运行的状态

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
};

#endif // CIRCUITSOLVERESULT_H
