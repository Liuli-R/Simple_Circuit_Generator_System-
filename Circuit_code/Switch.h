#pragma once

#include "Component.h"

class Switch : public Component {
private:
    bool closed; // 开关是否闭合

public:
    Switch(int id, double resistance = 0.0, bool closed=false);

    std::string getTypeName() const override;
    bool isClosed() const;
    void setClosed(bool state);
};
