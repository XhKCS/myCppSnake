#ifndef BOX_H
#define BOX_H

#include <QWidget>

const int box_width = 20;
const int box_height = 20;
enum box_types{SnakeBody, Food};

class Box
{
//    Q_OBJECT
public:
    int center_x;
    int center_y;
    int boxType;
public:
//    explicit Box(QWidget *parent = nullptr);
    Box(int center_x, int center_y, int boxType=0);
    ~Box();

    void setNewLocation(int x_new, int y_new);
    void rePaintBox(QWidget* showMat, int r, int g, int b, int a);

signals:

};

#endif // BOX_H
