#pragma once

#include "Component.h"

class Ammeter : public Component {
private:
    double I; // 电流表读数。

public:
    Ammeter(int id, double resistance = 0.0);

    std::string getTypeName() const override;
    double getI() const;
    void setI(double A);
};
