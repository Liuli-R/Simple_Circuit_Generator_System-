#include "ComponentAddController.h"

#include "Circuit_code/Ammeter.h"
#include "Circuit_code/Battery.h"
#include "Circuit_code/Bulb.h"
#include "Circuit_code/Circuit.h"
#include "Circuit_code/Fixed_resistor.h"
#include "Circuit_code/Voltmeter.h"
#include "Circuit_code/switch.h"
#include "Graphics/items/SwitchItem.h"
#include "Graphics/manager/ComponentItemManager.h"


ComponentAddController::ComponentAddController(Circuit &circuit, ComponentItemManager &itemManager)
    : circuit(circuit)
    , itemManager(itemManager)
{
}

void ComponentAddController::addBattery()
{
    auto *battery = new Battery(nextComponentId++,batteryVoltage);
    //创建电源根据设置好的电压值同步处理
    circuit.addComponent(battery);
    circuit.addNode();
    itemManager.addComponentItem(battery);
}

void ComponentAddController::addBulb()
{
    auto *bulb = new Bulb(nextComponentId++);
    circuit.addComponent(bulb);
    circuit.addNode();
    itemManager.addComponentItem(bulb);
}

void ComponentAddController::addAmmeter()
{
    auto *ammeter = new Ammeter(nextComponentId++);
    circuit.addComponent(ammeter);
    circuit.addNode();
    itemManager.addComponentItem(ammeter);
}

void ComponentAddController::addVoltmeter()
{
    auto *voltmeter = new Voltmeter(nextComponentId++);
    circuit.addComponent(voltmeter);
    //根据代码逻辑暂时不加入节点判断
    itemManager.addComponentItem(voltmeter);
}

void ComponentAddController::addSwitch()
{
    auto *switch1 = new Switch(nextComponentId++);
    circuit.addComponent(switch1);
    circuit.addNode();
    auto *item = itemManager.addComponentItem(switch1);
    auto *switchItem = dynamic_cast<SwitchItem *>(item);

    if (switchItem != nullptr)
    {
        switchItem->setStateChangedCallback([this](int componentId, bool closed) {
            auto *component = circuit.findComponentById(componentId);
            auto *sw = dynamic_cast<Switch *>(component);

            if (sw != nullptr)
            {
                sw->setClosed(closed);//将开关状态与对应模型状态同步
                if(switchStateChangedCallback)
                    switchStateChangedCallback();
            }
        });//这样就能完成双击同步改变状态
    }
}

void ComponentAddController::addResistor()
{
    auto *resistor = new Fixed_resistor(nextComponentId++);
    circuit.addComponent(resistor);
    circuit.addNode();
    itemManager.addComponentItem(resistor);
}

double ComponentAddController::getDefaultBatteryVoltage() const
{
    return batteryVoltage;
}

void  ComponentAddController::setDefaultBatteryVoltage(double batteryVoltage1)
{
    batteryVoltage=batteryVoltage1;
}

void ComponentAddController::resetIds()
{
    nextComponentId = 1;
}

void ComponentAddController::setSwitchStateChangedCallback(std::function<void()> callback)
{
    switchStateChangedCallback=std::move(callback);
}//同开关回调
