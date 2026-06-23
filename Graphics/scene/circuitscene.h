#ifndef CIRCUITSCENE_H
#define CIRCUITSCENE_H

#include <QGraphicsScene>

class CircuitScene : public QGraphicsScene
{
public:
    CircuitScene(QObject *parent = nullptr);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    //重写父类函数信号
};

#endif // CIRCUITSCENE_H
