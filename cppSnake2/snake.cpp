#include "snake.h"
//#include <QDebug>
#include <iostream>

//Snake::Snake(QWidget *parent) : QWidget(parent)
//{

//}

Snake::Snake(QWidget *parent, int head_x, int head_y, int direction, int size)
    :QWidget(parent), head_x(head_x), head_y(head_y), direction(direction), size(size)
{
    //在构造函数中要把snake的所有Box初始化好
    int box_x = head_x, box_y = head_y;
    boxes.clear();
    do {
         boxes.emplace_back( Box(box_x, box_y, SnakeBody) ); // 注意这里是尾插！
         switch (direction) {
             case Left:
                 box_x += box_width;
                 break;
             case Down:
                 box_y -= box_height;
                 break;
             case Right:
                 box_x -= box_width;
                 break;
             case Up:
                 box_y += box_height;
                 break;
             default:
                 std::cout << "wrong direction!\n";
                 break;
         }
     } while (boxes.size() < size);

//    std::cout << "Snake Constructed!";
}

Snake::~Snake()
{
//    std::cout << "Snake Destructed!";
}

void Snake::rePaintSnake(QWidget* showMat, int b, int g, int r, int a) {
    for (Box& box : this->boxes) {
        box.rePaintBox(showMat, r, g, b, a);
    }
}

//void Snake::paintEvent(QPaintEvent *event)
//{
//    QWidget::paintEvent(event);
//    for  (Box& box : boxes) {
//        box.rePaintBox(this, 255, 255, 0, 255);
//    }
//}

// 按照当前方向直线移动
void Snake::move(int key) { // 只需要改变坐标即可，显示的改变都在Game里做（整个画面全部重画）
    // 先移动后面的蛇身: 每一个Box的位置变为前一个Box的位置
    // 最后再根据方向移动蛇头
    int newDirection = -1;
    if (key == Qt::Key_A || key==Qt::Key_Left) {
        newDirection = Left;
    }
    else if (key == Qt::Key_S || key==Qt::Key_Down) {
        newDirection = Down;
    }
    else if (key == Qt::Key_D || key==Qt::Key_Right) {
        newDirection = Right;
    }
    else if (key == Qt::Key_W || key==Qt::Key_Up) {
        newDirection = Up;
    }
    if (newDirection != -1)
    { // 记得判断新方向是否是反向
        if ((direction == Left && newDirection != Right) || (direction == Down && newDirection != Up)
            || (direction == Right && newDirection != Left) || (direction == Up && newDirection != Down)) {
            direction = newDirection;
        }

    }

    switch (direction) { // 看清楚，别写出bug！
        case Left:
            head_x -= box_width;
            break;
        case Down:
            head_y += box_height;
            break;
        case Right:
            head_x += box_width;
            break;
        case Up:
            head_y -= box_height;
            break;
    }

    // 先让蛇身移动
    for (int i = boxes.size()-1; i > 0; --i) {
        boxes[i].center_x = boxes[i - 1].center_x;
        boxes[i].center_y = boxes[i - 1].center_y;

    }

    // 蛇头最后移动
    boxes[0].center_x = head_x;
    boxes[0].center_y = head_y;
}


bool Snake::getFood(Box &food) {
    if (abs(head_x-food.center_x) < box_width && abs(head_y-food.center_y) < box_height) {
        return true;
    }
    return false;
}

// 蛇头是否撞到蛇身
bool Snake::hasCrashed() {
    for (int i = 3; i < boxes.size(); ++i) { // 要想蛇头撞到蛇身，至少也要有4节长
        if (head_x == boxes[i].center_x && head_y == boxes[i].center_y) {
            return true;
        }
    }
    return false;
}


