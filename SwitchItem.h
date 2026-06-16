#ifndef SWITCHITEM_H
#define SWITCHITEM_H

#include "ComponentItem.h"
#include <functional>

class SwitchItem:public ComponentItem
{
    public:
        SwitchItem(int SwitchId,QGraphicsItem *parent=nullptr);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void setClosed(bool state);//设置
        bool isClosed() const;//访问
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        //务必记得这里对应的事件参数都是指针形式(报只有为虚函数声明才能时的错误优先检查)
        void setStateChangedCallback(std::function<void(int, bool)> callback);
    private:
        bool closed=false;
        std::function<void(int,bool)> stageChangedCallback;
        /*回调函数作用是接受外部传进来的函数指针
        或者lambda表达式等，同时将双击动作后更新完的
        状态以形参列表与实参一一对应的形式传出*/
        //这个不是函数指针而是功能比函数指针更强的函数包装器
};

#endif // SWITCHITEM_H
