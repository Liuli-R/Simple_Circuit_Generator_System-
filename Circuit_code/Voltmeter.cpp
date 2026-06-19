#include "Voltmeter.h"

Voltmeter::Voltmeter(int id, double resistance)
    : Component(id, resistance)
    , U(0.0)
{
}

std::string Voltmeter::getTypeName() const
{
    return "voltmeter";
}

double Voltmeter::getU() const
{
    return U;
}

void Voltmeter::setU(double V)
{
    U = V;
}
