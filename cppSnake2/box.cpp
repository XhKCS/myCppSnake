#include "box.h"
//#include <QDebug>
#include <iostream>
#include <QPainter>

//Box::Box(QWidget *parent) : QWidget(parent)
//{

//}

Box::Box(int center_x, int center_y, int boxType)
    :center_x(center_x), center_y(center_y), boxType(boxType)
{
//    std::cout << "Box Constructed!";
}

Box::~Box() {
//    std::cout << "Box Destructed!";
}

void Box::setNewLocation(int x_new, int y_new)
{
    this->center_x = x_new;
    this->center_y = y_new;
}

void Box::rePaintBox(QWidget *showMat, int r, int g, int b, int a)
{
    QPainter painter(showMat); //设置在showMat上绘画
    QPen pen1; //创建画笔
    QBrush brush1; //创建画刷
    pen1.setColor(QColor(r, g, b, 255)); //设置颜色
    brush1.setColor(QColor(r, g, b, a));
    brush1.setStyle(Qt::BrushStyle::SolidPattern);

    painter.setPen(pen1);
    painter.setBrush(brush1);
    painter.drawRect(center_x - box_width/2.0, center_y - box_height/2.0,
                     box_width, box_height);
}
