#include "Battery.h"

Battery::Battery(int id, double voltage)
    : Component(id, 0.0), voltage(voltage) {}

std::string Battery::getTypeName() const {
    return "battery";
}

double Battery::getVoltage() const {
    return voltage;
}
