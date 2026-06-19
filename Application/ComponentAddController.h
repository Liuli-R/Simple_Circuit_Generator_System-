#ifndef COMPONENTADDCONTROLLER_H
#define COMPONENTADDCONTROLLER_H

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

    void resetIds();

private:
    Circuit &circuit;
    ComponentItemManager &itemManager;
    int nextComponentId = 1;
};

#endif // COMPONENTADDCONTROLLER_H
