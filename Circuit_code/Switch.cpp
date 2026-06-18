#include "Switch.h"

Switch::Switch(int id, double resistance, bool closed)
    :Component(id,resistance),closed(closed)
{
}

std::string Switch::getTypeName() const
{
    return "switch";
}

bool Switch::isClosed() const
{
    return closed;
}

void Switch::setClosed(bool state)
{
    closed=state;
}