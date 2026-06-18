#pragma once

#include "Component.h"

class Fixed_resistor : public Component {
public:
    Fixed_resistor(int id, double resistance = 5.0);

    std::string getTypeName() const override;
};
