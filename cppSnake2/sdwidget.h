#ifndef SDWIDGET_H
#define SDWIDGET_H

#include <QWidget>
#include "gamewidget.h"

namespace Ui {
class SDWidget;
}

class SDWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget *game = nullptr;
    QWidget *backWidget;

public:
    explicit SDWidget(QWidget *backWidget, QWidget *parent = nullptr);
    ~SDWidget();

    void paintEvent(QPaintEvent *event);

private slots:

    void on_confirmButton_clicked();

    void on_backButton_clicked();

private:
    Ui::SDWidget *ui;
};

#endif // SDWIDGET_H
