#ifndef CIRCUITLAYOUTBUILDER_H
#define CIRCUITLAYOUTBUILDER_H

class Circuit;
class ComponentItemManager;
class QRectF;
class CircuitLayout;

class CircuitLayoutBuilder
{
    public:
        CircuitLayoutBuilder();
        CircuitLayout build(const Circuit &circuit,const ComponentItemManager &manager,const QRectF &sceneRect);
};

#endif // CIRCUITLAYOUTBUILDER_H
