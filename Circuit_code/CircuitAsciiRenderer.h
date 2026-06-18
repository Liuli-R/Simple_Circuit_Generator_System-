#pragma once

#include <string>
#include "Circuit.h"

class CircuitAsciiRenderer {
public:
    std::string render(const Circuit& circuit);
};
