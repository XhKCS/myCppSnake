#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QPainter>
#include <iostream>
#include <QKeyEvent>
#include <QPainter>
#include "recordwidget.h"

GameWidget::GameWidget(QWidget *backWidget, QWidget *parent, int difficultyDegree) :
    QWidget(parent),
    snake(this, 400, 400, rand()%4, 3),
    food(100, 100, 1),
    backWidget(backWidget),
    difficultyDegree(difficultyDegree),
    currentTime(0),
    score(0),
    gamePaused(true),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    ui->overLabel->setVisible(false);
    ui->confirmButton->setVisible(false);
    QPixmap pixmap(":/res/playBtn.jpg");
    ui->playButton->setIcon(QIcon(pixmap));
    ui->playButton->setIconSize(ui->playButton->size());

    this->totalTimer = new QTimer(this); //要连接到对象树
    this->intervalTimer = new QTimer(this);
    switch (this->difficultyDegree) {
        case easy:
            this->interval = 400;
            break;
        case middle:
            this->interval = 240;
            break;
        case hard:
            this->interval = 100;
            break;
    }
    changeFoodLocation();

    connect(totalTimer, &QTimer::timeout, [=]() {
        //ui控件显示递增的时间数字
        ui->playTimeLcd->display(++currentTime);
    });
    connect(intervalTimer, &QTimer::timeout, this, &GameWidget::oneStep);

    connect(this, &GameWidget::gameHasOvered, this, &GameWidget::showGameOver);
//    this->update();

    this->setAttribute(Qt::WA_DeleteOnClose);

}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::changeFoodLocation()
{   //只要判断不与当前蛇的身体重合即可
    bool isOK = false;
    int location_x, location_y;
    while (!isOK)
    {
           location_x = start_X + 10 + (rand()%(ground_width / box_width)) * box_width;
           location_y = start_Y + 10 + (rand()%(ground_height / box_height)) * box_height;
           bool isOverlap = false;
           for (Box& box : snake.boxes) {
               if (abs(location_x - box.center_x) <= box_width && abs(location_y - box.center_y) <= box_height) {
                   isOverlap = true;
                   break;
               }
           }
           if (!isOverlap) {
               food.center_x = location_x;
               food.center_y = location_y;
               isOK = true;
           }
    }

}

void GameWidget::launchTimers()
{
    totalTimer->start(1000);
    intervalTimer->start(this->interval);
}

bool GameWidget::gameOver()
{
    if (snake.head_x <= start_X+box_width/2.0 || snake.head_x >= start_X + ground_width-box_width/2.0 ||
            snake.head_y <= start_Y+box_height/2.0 || snake.head_y >= start_Y + ground_height-box_height/2.0
            || snake.hasCrashed())
    {
            return true;
    }
    return false;
}

void GameWidget::pauseOrPlay()
{
    if (!gameOver())
    {
        if (gamePaused == true) {
            //启动游戏
            gamePaused = false;
            QPixmap pixmap(":/res/pauseBtn.jpg");
            ui->playButton->setIcon(QIcon(pixmap));
            ui->playButton->setIconSize(ui->playButton->size());
            launchTimers();
        }
        else if (gamePaused == false) {
            //暂停游戏
            gamePaused = true;
            QPixmap pixmap(":/res/playBtn.jpg");
            ui->playButton->setIcon(QIcon(pixmap));
            ui->playButton->setIconSize(ui->playButton->size());
            totalTimer->stop();
            intervalTimer->stop();
        }
    }
}

void GameWidget::oneStep()
{
    if (gameOver()==false)
    {
        int oldScore = score;
        snake.move(currentKeyPress);

        if (gameOver())
        {
            emit gameHasOvered();
        }

        else if (snake.getFood(food)) {
                  snake.head_x = food.center_x;
                  snake.head_y = food.center_y; // 别忘记
                  snake.boxes.emplace_front(Box(food)); //首插

                  score += 20;
                  interval = std::max(40, interval-15);
                  ui->currentScoreLcd->display(score);
                  changeFoodLocation();
        }
        if (score != oldScore && score%100==0){
            changeRandomColor();
        }
        this->update(); // 更新显示的视图
        ui->currentScoreLcd->display(score);
    }

}

void GameWidget::changeRandomColor()
{
    this->R = 0 + rand()%256;
    this->G = 0 + rand()%256;
    this->B = 0 + rand()%256;
    this->A = 0 + rand()%200;
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/bg.jpg"));

    QPen pen1; //创建画笔
    QBrush brush1; //创建画刷
    pen1.setColor(QColor(0, 0, 0, 255)); //设置颜色
    pen1.setWidth(3);
    brush1.setColor(QColor(R, G, B, A));
    brush1.setStyle(Qt::BrushStyle::SolidPattern);

    painter.setPen(pen1);
    painter.setBrush(brush1);
    painter.drawRect(start_X, start_Y, ground_width, ground_height);

    snake.rePaintSnake(this, 255, 255, 0, 255);
    food.rePaintBox(this, 255, 0, 0, 255);
}

bool GameWidget::event(QEvent *e)
{
    if (e->type()==QEvent::KeyPress)
    {
        this->keyPressEvent(static_cast<QKeyEvent *>(e));
        return true;
    }
    return QWidget::event(e);
}

void GameWidget::keyPressEvent(QKeyEvent *ke)
{

    if (ke->key()==Qt::Key_Space)
    {
        this->pauseOrPlay();
    }

    currentKeyPress = ke->key();

}

//槽
void GameWidget::on_playButton_clicked()
{
    this->pauseOrPlay();
}

void GameWidget::showGameOver()
{
    totalTimer->stop();
    intervalTimer->stop();
    QPainter painter(this);
    QPen pen1;
    pen1.setColor(QColor(255, 0, 0));
    pen1.setWidth(3);
    painter.setPen(pen1);
//    painter.drawText(start_X, start_Y, ">.< Game Over!"); //该函数不起作用了
    ui->overLabel->setVisible(true);
    ui->confirmButton->setVisible(true);

}


void GameWidget::on_confirmButton_clicked()
{
    RecordWidget *recordWidget = new RecordWidget(backWidget, currentTime, score, "records.txt", nullptr);
    recordWidget->show();
    this->close();
}

