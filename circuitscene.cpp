#include "circuitscene.h"
#include <QPainter>

CircuitScene::CircuitScene(QObject *parent)
{
    setSceneRect(0, 0, 900, 650);
    //限定画布的范围
}

void CircuitScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    //1.先铺一个淡绿色/淡灰色底色
    painter->fillRect(rect, QColor(248,255,251));

    const int gridSize = 20;      // 小网格间距
    const int bigGridSize = 100;  // 大网格间距

    //2.计算当前可见区域内第一条网格线的位置
    //floor向下取整 ceil向上取整
    int left = static_cast<int>(std::floor(rect.left()));
    int right = static_cast<int>(std::ceil(rect.right()));
    int top = static_cast<int>(std::floor(rect.top()));
    int bottom = static_cast<int>(std::ceil(rect.bottom()));

    int firstLeft = left - (left % gridSize);
    int firstTop = top - (top % gridSize);

    //3.画细网格线
    QPen smallGridPen(QColor(187, 247, 208, 120)); // 淡绿色
    smallGridPen.setWidth(1);
    painter->setPen(smallGridPen);

    for (int x = firstLeft; x <= right; x += gridSize)
    {
        painter->drawLine(x, top, x, bottom);
        //采用从(x1,y1)到(x2,y2)的方式进行绘制网格线
    }

    for (int y = firstTop; y <= bottom; y += gridSize)
    {
        painter->drawLine(left, y, right, y);
    }

    //4.每隔 100px 画一条稍微明显的大网格线
    QPen bigGridPen(QColor(74, 222, 128, 120));
    bigGridPen.setWidth(1);
    painter->setPen(bigGridPen);

    int firstBigLeft = left - (left % bigGridSize);
    int firstBigTop = top - (top % bigGridSize);

    for (int x = firstBigLeft; x <= right; x += bigGridSize)
    {
        painter->drawLine(x, top, x, bottom);
    }

    for (int y = firstBigTop; y <= bottom; y += bigGridSize)
    {
        painter->drawLine(left, y, right, y);
    }
}