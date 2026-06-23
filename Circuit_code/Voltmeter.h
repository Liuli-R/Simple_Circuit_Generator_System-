#pragma once

#include <limits>
#include "Component.h"

class Voltmeter : public Component
{
private:
    double U; // 电压表读数
    int targetComponentId = -1;// 电压表所测元器件id

public:
    Voltmeter(int id, double resistance = std::numeric_limits<double>::infinity());

    std::string getTypeName() const override;
    double getU() const;
    void setU(double V);
    void setTargetComponentId(int id);
    int getTargetComponentId() const;
};
