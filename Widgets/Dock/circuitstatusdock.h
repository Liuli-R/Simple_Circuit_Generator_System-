#ifndef CIRCUITSTATUSDOCK_H
#define CIRCUITSTATUSDOCK_H

#include "Circuit_code/CircuitSolveResult.h"

#include <QDockWidget>
#include <vector>

class QMovie;//只用到指针所以只声明一个class

namespace Ui {
class CircuitStatusDock;
}

class CircuitStatusDock : public QDockWidget
{
    Q_OBJECT

public:
    CircuitStatusDock(QWidget *parent = nullptr);
    ~CircuitStatusDock() override;

    //根据一次完整的电路计算结果更新显示五组显示信息
    void updateResult(const CircuitSolveResult &result);
    //清空电路后dock面板恢复到默认状态
    void resetDisplay();

private:
    void setupAnimation();//加载并启动底部 GIF
    //新增函数->用来处理多个电压表问题
    void updateSelectedVoltmeter(int index);

    Ui::CircuitStatusDock *ui = nullptr;
    QMovie *movie = nullptr;
    //存储多个电压表计算结果的vector
    std::vector<VoltmeterSolveResult> voltmeterResults;
};

#endif
