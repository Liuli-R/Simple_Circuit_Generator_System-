#ifndef COMPONENTITEM_H
#define COMPONENTITEM_H

#include <QGraphicsItem>

class ComponentItem
{
    public:
        ComponentItem(int componentId,QGraphicsItem *parent=nullptr);
        //构造函数用来绘制所对应元器件的对象
        int getComponentId() const;
        //用来获取当前元器件id的访问器函数
        QRectF boundingRect() const;
        //用来限制所画元器件图形的矩形限制框
        QPointF leftPointScenePos() const;
        //用来设置元器件所对应左端点的场景位置
        QPointF rightPointScenePos() const;
        //用来设置元器件所对应右端点的场景位置

    private:
        int id;
};

#endif // COMPONENTITEM_H
