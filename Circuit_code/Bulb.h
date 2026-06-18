#pragma once

#include "Component.h"

class Bulb : public Component {
private:
    bool isLit; // 灯泡是否点亮。

public:
    Bulb(int id, double resistance = 10.0);

    std::string getTypeName() const override;
    void setLit(bool lit);
    bool isLitState() const;
};
