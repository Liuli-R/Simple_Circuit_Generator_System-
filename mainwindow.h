#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "Graphics/manager/ComponentItemManager.h"
#include "Circuit_code/Circuit.h"
#include "Circuit_code/CircuitSolver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setupScene();
    void setupRunButton();
    void setupConnections();

    void buildCircuit();
    void drawCircuit();//绘制电路
    void clearCircuit();//清空电路重新来过
    void updateCircuitState(bool switchClosed);//更新电路运行状态
    void updateScene();
    //以下都是预备为槽函数进行与对应按钮进行连接的作用
    void addBattery();
    void addBulb();
    void addResistor();
    void addAmmeter();
    void addVoltmeter();
    void addSwitch();

    //提供给CircuitSolver的接口函数获取整个电路模型
    //进行了函数重载->类似实习题目中的安全数组模板类的用途
    Circuit& getCircuit();
    const Circuit& getCircuit() const;
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene=nullptr;
    int nextComponentId = 1;
    QAction *runAction = nullptr;
    Circuit circuit;//整体电路模型
    CircuitSolver solver;//负责计算整个电路的"计算器"
    ComponentItemManager *itemManager=nullptr;//负责管理整个图形系统
};
#endif // MAINWINDOW_H
