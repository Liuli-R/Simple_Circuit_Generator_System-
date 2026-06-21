#ifndef COMPONENTADDCONTROLLER_H
#define COMPONENTADDCONTROLLER_H

#include <functional>

class Circuit;
class ComponentItemManager;

class ComponentAddController
{
public:
    ComponentAddController(Circuit &circuit, ComponentItemManager &itemManager);

    void addBattery();
    void addBulb();
    void addAmmeter();
    void addVoltmeter();
    void addSwitch();
    void addResistor();

    double getDefaultBatteryVoltage() const;
    void setDefaultBatteryVoltage(double batteryVoltage1);
    //为窗口设置准备的获取默认电压和获取当前设置电压

    void resetIds();
    void setSwitchStateChangedCallback(std::function<void()> callback);

private:
    Circuit &circuit;
    ComponentItemManager &itemManager;
    int nextComponentId = 1;
    double batteryVoltage = 9.0;
    std::function<void()> switchStateChangedCallback;
    //状态回调函数目的是实现版半实时化配合开关回调
};

#endif // COMPONENTADDCONTROLLER_H
