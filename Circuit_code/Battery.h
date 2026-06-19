#pragma once

#include "Component.h"

class Battery : public Component
{
private:
    double voltage; // 电源电压。

public:
    Battery(int id, double voltage = 9.0, double resistance = 0.0);

    std::string getTypeName() const override;
    double getVoltage() const;
};
