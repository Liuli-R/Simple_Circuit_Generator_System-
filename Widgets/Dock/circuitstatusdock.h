#ifndef CIRCUITSTATUSDOCK_H
#define CIRCUITSTATUSDOCK_H

#include <QDockWidget>

class QMovie;//只用到指针所以只声明一个class
struct CircuitSolveResult;

namespace Ui {
class CircuitStatusDock;
}

class CircuitStatusDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit CircuitStatusDock(QWidget *parent = nullptr);
    ~CircuitStatusDock() override;

    // 根据一次完整的电路计算结果更新五组显示信息
    void updateResult(const CircuitSolveResult &result);

    // 清空电路后恢复为默认显示状态
    void resetDisplay();

private:
    // 加载并启动底部 GIF
    void setupAnimation();

    Ui::CircuitStatusDock *ui = nullptr;
    QMovie *movie = nullptr;
};

#endif // CIRCUITSTATUSDOCK_H
