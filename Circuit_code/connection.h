#pragma once

#include "Component.h"

class Connection {
private:
    Component* m_leftComp;
    Component* m_rightComp;
    int numberNode;

public:
    Connection(Component* leftComp, Component* rightComp, int nodeId = -1);
    ~Connection();

    Component* getLeftComponent() const;
    Component* getRightComponent() const;

    int getNodeId() const;
    void setNodeId(int nodeId);

    void connection();
};
