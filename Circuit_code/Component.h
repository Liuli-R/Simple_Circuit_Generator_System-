#pragma once

#include <string>

class Component
{
protected:
    double resistance;    // 元件电阻值。
    int leftNodeId = -1;  // 左端口连接的节点 ID，-1 表示未连接。
    int rightNodeId = -1; // 右端口连接的节点 ID，-1 表示未连接。
    int id;               // 元件唯一编号，由外部创建元件时传入。
    std::string typeName;

public:
    Component(int id, double resistance = 0.0);
    virtual ~Component();

    int getId() const;
    double getResistance() const;
    int getLeftNodeId() const;
    int getRightNodeId() const;

    // 设置元件左右端口连接到哪个节点。
    void setLeftNode(int nodeId);
    void setRightNode(int nodeId);

    // 默认认为元件可导通，特殊元件可在派生类中重写。
    virtual bool canConduct() const;
    // 返回固定类型名，例如 battery、bulb、ammeter。
    virtual std::string getTypeName() const = 0;
};
