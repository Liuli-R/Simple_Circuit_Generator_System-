#include "Fixed_resistor.h"

Fixed_resistor::Fixed_resistor(int id, double resistance)
    : Component(id, resistance) {}

void Fixed_resistor::setResistance(double r1)
{
    resistance=r1;
}

std::string Fixed_resistor::getTypeName() const {
    return "resistor";
}
