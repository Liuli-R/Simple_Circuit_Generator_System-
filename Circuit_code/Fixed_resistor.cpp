#include "Fixed_resistor.h"

Fixed_resistor::Fixed_resistor(int id, double resistance)
    : Component(id, resistance) {}

std::string Fixed_resistor::getTypeName() const {
    return "resistor";
}
