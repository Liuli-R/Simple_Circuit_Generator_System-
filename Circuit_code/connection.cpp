#include "connection.h"

Connection::Connection(Component *leftComp, Component *rightComp, int nodeId)
    : m_leftComp(leftComp)
    , m_rightComp(rightComp)
    , numberNode(nodeId)
{
}

Connection::~Connection()
{
}

Component *Connection::getLeftComponent() const
{
    return m_leftComp;
}

Component *Connection::getRightComponent() const
{
    return m_rightComp;
}

int Connection::getNodeId() const
{
    return numberNode;
}

void Connection::setNodeId(int nodeId)
{
    numberNode = nodeId;
}

void Connection::connection()
{
    if (m_leftComp == nullptr || m_rightComp == nullptr)
        return;

    int nodeId = numberNode;
    if (nodeId == -1 && m_leftComp->getRightNodeId() != -1) {
        nodeId = m_leftComp->getRightNodeId();
    }
    if (nodeId == -1 && m_rightComp->getLeftNodeId() != -1) {
        nodeId = m_rightComp->getLeftNodeId();
    }
    if (nodeId == -1) {
        return;
    }

    m_leftComp->setRightNode(nodeId);
    m_rightComp->setLeftNode(nodeId);
}
