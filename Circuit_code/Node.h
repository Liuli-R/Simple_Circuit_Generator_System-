#pragma once

class Node
{
private:
    int id;
    int x; // 预留坐标，供 Qt 图形渲染使用。
    int y;

public:
    Node(int id, int x = 0, int y = 0);

    int getId() const;
    int getX() const;
    int getY() const;
    void setPos(int x, int y);
};
