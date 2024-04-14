#include "mypushbutton.h"

//MyPushButton::MyPushButton(QObject *parent) : QPushButton()
//{

//}

MyPushButton::MyPushButton(QString backimg)
{
    //normal image path
    this->backImg = backImg;

    //press image path
//    this->pressImg=pressImg;

    QPixmap pix;
    //loag normalImg
    pix.load(backImg);

    //set fixed size
    this->setFixedSize(pix.width(), pix.height());

    //set style sheet
    this->setStyleSheet("QPushButton{border:0px;}");

    //set icon
    this->setIcon(pix);

    //set icon size
    this->setIconSize(QSize(pix.width(), pix.height()));
}
