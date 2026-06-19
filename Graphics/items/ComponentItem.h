#ifndef COMPONENTITEM_H
#define COMPONENTITEM_H

#include <QGraphicsItem>
#include <QVariant>

//公有继承QGraphicsItem由图形条目到元器件条目
class ComponentItem:public QGraphicsItem
{
    public:
        ComponentItem(int componentId,QGraphicsItem *parent=nullptr);
        //构造函数用来绘制所对应元器件的对象
        int getComponentId() const;
        //用来获取当前元器件id的访问器函数
        QRectF boundingRect() const override;
        //用来限制所画元器件图形的矩形限制框
        QPointF leftPointScenePos() const;
        //用来设置元器件所对应左端点的场景位置
        QPointF rightPointScenePos() const;
        //用来设置元器件所对应右端点的场景位置
        //用来重写鼠标按下选中事件来配合更新鼠标图标
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    protected:
        void drawTerminals(QPainter *painter) const;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
        //限制可移动边界所用的边界约束防止移出画布所在范围 重写QGraphicsItem的成员函数
    private:
        int id;
};

#endif // COMPONENTITEM_H
