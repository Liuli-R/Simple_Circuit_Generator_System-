#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Circuit_code/Circuit.h"
#include "Circuit_code/CircuitSolver.h"

class QAction;
class QGraphicsScene;
class ComponentAddController;
class ComponentItemManager;
class WireManager;
class TopActionWidget;
class CircuitStatusDock;

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
    void setupActions();
    void setupMenus();
    void setupTopActionWidget();
    void setupStatusDock();
    void setupConnections();
    bool areAllSwitchesClosed() const;
    bool isCircuitClosed() const;

    void buildCircuit();
    void runCircuit();//运行电路整合
    void clearCircuit();//清空电路重新来过
    void updateCircuitState();//更新电路运行状态
    void updateScene();//刷新电路比如灯泡亮暗状态
    void openGuideDialog();
    void openSettingsDialog();
    //提供给CircuitSolver的接口函数获取整个电路模型
    //进行了函数重载->类似实习题目中的安全数组模板类的用途
    Circuit &getCircuit();
    const Circuit &getCircuit() const;
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene = nullptr;
    QAction *runAction = nullptr;//菜单栏右边控件按钮集成
    QAction *clearAction = nullptr;
    QAction *settingsAction = nullptr;//电路初始参数设置
    QAction *guideAction = nullptr;//帮助手册
    //主界面窗口部件
    TopActionWidget *topActionWidget = nullptr;
    CircuitStatusDock *statusDock = nullptr;

    Circuit circuit;//整体电路模型
    CircuitSolver solver;//负责计算整个电路的"计算器"
    bool circuitPrepared = false;//半实时模式的所需变量
    ComponentItemManager *itemManager = nullptr;//负责管理整个图形系统
    WireManager *wireManager = nullptr;//负责管理导线图形
    ComponentAddController *componentAddController = nullptr;//负责添加元器件
};
#endif // MAINWINDOW_H
