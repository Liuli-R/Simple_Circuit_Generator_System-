#pragma once

#include <string>
#include <vector>
#include "Component.h"

class CircuitModel {
private:
    // components 保存原始添加顺序，orderedComponents 保存电源排前后的顺序。
    std::vector<Component*> components;
    std::vector<Component*> orderedComponents;

    const std::vector<Component*>& currentComponents() const;

public:
    // 添加元件，返回当前已保存的元件数量。
    int Cconstruct(Component* comp);
    // 按简单串联规则分配节点。
    void connection();

    bool isClosedLoop() const;
    // 获取电压表当前粗略测量到的元件类型名。
    std::string getvc() const;

    // getR/getV/getU 用于简单串联电路的基础计算。
    double getR() const;
    double getV() const;
    double getU() const;
    double getRV() const;

    void setI(double A);
    void setlight(bool lit);
    void setU(double V);
};
