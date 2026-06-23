#include "ComponentItem.h"

#include <QColor>
#include <QCursor>
//用来更改框画对应元器件的鼠标样式
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QRectF>
//以上三者全为绘画时填充内部或描绘外壳的工具

ComponentItem::ComponentItem(int componentId, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , id(componentId)
{
    //setFlag功能开关
    //设计可以让元器件物品被选中被移动
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    //使鼠标移到元器件物品上面鼠标图标显示小手
    setCursor(Qt::OpenHandCursor);
    //使鼠标选中该元器件物品时鼠标图标显示小手抓紧
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //使画布内物体反馈图形几何变化 需要回调函数
}

int ComponentItem::getComponentId() const
{
    return id;
    //获取对应id
}

QRectF ComponentItem::boundingRect() const
{
    return QRectF(-70, -52, 140, 104);
    //目的时框定元器件出现的区域
}

QPointF ComponentItem::leftPointScenePos() const
{
    return mapToScene(QPointF(-55, 0));
    //目的是定位到场景的真实坐标
}

QPointF ComponentItem::rightPointScenePos() const
{
    return mapToScene(QPointF(55, 0));
    //目的时定位到场景的真实坐标
}

void ComponentItem::drawTerminals(QPainter *painter) const
{
    painter->setPen(QPen(QColor(0, 0, 0), 2.0, Qt::SolidLine, Qt::RoundCap));
    //第一种临时构造匿名对象右值引用绑定
    //QPen的临时构造参数又采用了隐式转换将QColor转换为QBrush->构造函数
    //设计样式的边为实线和圆边
    painter->drawLine(QPointF(-55, 0), QPointF(-38, 0));
    //画的是两侧接线的导线
    painter->drawLine(QPointF(38, 0), QPointF(55, 0));

    //画的是接线两侧的断点
    painter->setPen(Qt::NoPen);
    //不画轮廓线 画两边的端点用绿色实心小圆点代替
    painter->setBrush(QColor(34, 197, 94));
    painter->drawEllipse(QPointF(-55, 0), 4, 4);
    painter->drawEllipse(QPointF(55, 0), 4, 4);
}

QVariant ComponentItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //QVariant可以理解为Qt中的"Union"
    if (change == QGraphicsItem::ItemPositionChange && scene() != nullptr)
    {
        QPointF newPos = value.toPointF();

        QRectF sceneBounds = scene()->sceneRect();
        //scene()获取当前物体所处场景指针 同时获取场景所在矩形区域
        QRectF itemBounds = boundingRect();
        //获取物体所在边界

        qreal minX = sceneBounds.left() - itemBounds.left();
        qreal maxX = sceneBounds.right() - itemBounds.right();
        qreal minY = sceneBounds.top() - itemBounds.top();
        qreal maxY = sceneBounds.bottom() - itemBounds.bottom();

        newPos.setX(qBound(minX, newPos.x(), maxX));
        newPos.setY(qBound(minY, newPos.y(), maxY));
        //限定整体的移动范围

        return newPos;
        //不选择setPos()方式是为了防止递归调用
    }

    return QGraphicsItem::itemChange(change, value);
}

void ComponentItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
    QGraphicsItem::mousePressEvent(event);
    //把处理地默认权交回给界面的可移动，选中
    //否则可能会触发事件的传递截断
}

void ComponentItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    QGraphicsItem::mouseReleaseEvent(event);
    //松开鼠标默认更换图标为原图标处理
}





