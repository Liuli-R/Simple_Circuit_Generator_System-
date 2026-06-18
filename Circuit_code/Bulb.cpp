#include "Bulb.h"

Bulb::Bulb(int id, double resistance, bool isLit)
    : Component(id, resistance), isLit(isLit) {}

std::string Bulb::getTypeName() const {
    return "bulb";
}

void Bulb::setLit(bool lit) {
    isLit = lit;
}

bool Bulb::isLitState() const {
    return isLit;
}
