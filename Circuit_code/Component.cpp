#include "Component.h"

Component::Component(int id, double resistance)
    : id(id), resistance(resistance) {}

Component::~Component() {}

int Component::getId() const { return id; }
double Component::getResistance() const { return resistance; }
int Component::getLeftNodeId() const { return leftNodeId; }
int Component::getRightNodeId() const { return rightNodeId; }

void Component::setLeftNode(int nodeId) { leftNodeId = nodeId; }
void Component::setRightNode(int nodeId) { rightNodeId = nodeId; }

bool Component::canConduct() const { return true; }