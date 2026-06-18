#include "Node.h"

Node::Node(int id, int x, int y) : id(id), x(x), y(y) {}

int Node::getId() const { return id; }
int Node::getX() const { return x; }
int Node::getY() const { return y; }
void Node::setPos(int x, int y) { this->x = x; this->y = y; }

