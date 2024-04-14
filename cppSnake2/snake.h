#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <deque>

#include "Box.h"
enum directions{Left, Down, Right, Up}; // 枚举4种方向

class Snake : public QWidget
{
    Q_OBJECT
public:
    int head_x;
    int head_y; // 蛇头中心点的坐标
    int direction; // 蛇当前正在面向的方向
    int size;
    std::deque<Box> boxes;
public:
    Snake(QWidget *parent, int head_x, int head_y, int direction, int size = 3);
    ~Snake();

    void move(int key); // 自动直线前进和转弯应该集成到一起，若key==-1则继续直线移动
  //    void turning(int newDirection); // 向新方向转弯
    bool getFood(Box& food);
    bool hasCrashed(); // 判断是否蛇头撞到蛇身
    void rePaintSnake(QWidget* showMat, int r, int g, int b, int a);

//    void paintEvent(QPaintEvent* event);
signals:

};

#endif // SNAKE_H
