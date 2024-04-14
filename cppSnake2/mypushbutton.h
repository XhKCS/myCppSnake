#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QObject *parent = nullptr);
    MyPushButton(QString backImg);

    QString backImg;

signals:

};

#endif // MYPUSHBUTTON_H
