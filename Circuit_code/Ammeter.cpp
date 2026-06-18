#include "Ammeter.h"

Ammeter::Ammeter(int id, double resistance)
    : Component(id, resistance), I(0.0) {}

std::string Ammeter::getTypeName() const {
    return "ammeter";
}

double Ammeter::getI() const {
    return I;
}

void Ammeter::setI(double A) {
    I = A;
}
