#include "sdwidget.h"
#include "ui_sdwidget.h"
#include "gamewidget.h"
#include <QPainter>

SDWidget::SDWidget(QWidget *backWidget, QWidget *parent) :
    QWidget(parent),
    backWidget(backWidget),
    ui(new Ui::SDWidget)
{
    ui->setupUi(this);
}

SDWidget::~SDWidget()
{
    delete ui;
}

void SDWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/bg3.jpg"));
}


void SDWidget::on_confirmButton_clicked()
{

    if (ui->radioBtnEasy->isChecked()) {
        game = new GameWidget(backWidget, nullptr, 0);
    }
    else if (ui->radioBtnMedium->isChecked()) {
        game = new GameWidget(backWidget, nullptr, 1);
    }
    else if (ui->radioBtnHard->isChecked()) {
        game = new GameWidget(backWidget, nullptr, 2);
    }

    if (game != nullptr)
    {
        game->show();
    }

    this->close();
}


void SDWidget::on_backButton_clicked()
{
    backWidget->showNormal();
    this->close();
}

