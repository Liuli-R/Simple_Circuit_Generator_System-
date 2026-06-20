#pragma once

#include <vector>

class Component;
class Node;
class Voltmeter;

class Circuit
{
private:
    //Circuit 持有这些裸指针，并在析构函数中释放
    std::vector<Component *> components;
    std::vector<Node *> nodes;
    int nextNodeId = 1;

public:
    Circuit();
    ~Circuit();

    //添加元件 元件 ID 由创建元件时传入，这里只负责保存指针
    Component *addComponent(Component *comp);
    //添加节点并返回节点 ID，坐标供 Qt 绘图使用
    int addNode(int x = 0, int y = 0);

    //将元件左/右端口连接到指定节点
    void connectLeft(Component *comp, int nodeId);
    void connectRight(Component *comp, int nodeId);

    //获取所有元件和节点，主要供界面层读取
    const std::vector<Component *> getMainLoopComponents() const;
    const std::vector<Component *> &getComponents() const;
    const std::vector<Node *> &getNodes() const;

    //判断当前电路是否拥有电源 电流表 电压表 便于后续电路判断
    bool hasBattery() const;
    bool hasAmmeter() const;
    bool hasVoltmeter() const;
    //判断当前元件是否形成简单闭合串联回路
    bool isClosedLoop() const;
    //按元件和节点的添加顺序自动构造一个简单串联闭环
    bool buildClosedLoop();
    //合并CircuitModel原先职能的一部分操作
    Component *findComponentById(int id) const;//根据id查找元器件
    int getComponentCount() const;
    //新加更好服务图形化的接口
    void connectVoltmeterTo(Voltmeter *meter, Component *target);
    void clearCircuit();
};
