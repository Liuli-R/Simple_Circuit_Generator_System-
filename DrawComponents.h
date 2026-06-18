#ifndef DRAWCOMPONENTS_H
#define DRAWCOMPONENTS_H

#include "Graphics/ComponentItem.h"
#include <vector>

class DrawComponents
{
private:
    std::vector<ComponentItem *>ComponentItems;
public:
    DrawComponents();
    void addComponentItems(ComponentItem *comp);
    void updateComponentItem();
    void clearComponentItems();
};

#endif // DRAWCOMPONENTS_H
