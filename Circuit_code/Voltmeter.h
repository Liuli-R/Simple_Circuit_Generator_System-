#pragma once

#include <limits>
#include "Component.h"

class Voltmeter : public Component
{
private:
    double U; // 电压表读数。

public:
    Voltmeter(int id, double resistance = std::numeric_limits<double>::infinity());

    std::string getTypeName() const override;
    double getU() const;
    void setU(double V);
};
