#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "snake.h"
#include <QEvent>
#include <QTimer>

#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class GameWidget;
}

const int start_X = 100, start_Y = 200;
const int ground_width = 1400; //
const int ground_height = 760;

enum difficulty_degrees{easy, middle, hard};

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    Snake snake; //蛇
    Box food; // 食物（每次被吃后会更新位置）

    QWidget* backWidget;
    int difficultyDegree;
    int interval; //每一步的时间间隔（越短难度越高）
    int R = 255, G = 255, B = 240, A = 160; //游戏场地的背景色

    int currentTime = 0;
    int score = 0;

    int currentKeyPress = -1; //当前玩家按下的键盘值
    bool gamePaused; //记录游戏状态：是否暂停
    QTimer *totalTimer; //游戏时长定时器
    QTimer *intervalTimer; //蛇移动的定时器

    QMediaPlayer player;

public:
    explicit GameWidget(QWidget *backWidget, QWidget *parent = nullptr, int difficultyDegree = 0);
    ~GameWidget();

    void changeFoodLocation();
    void launchTimers();
    bool gameOver();
    void pauseOrPlay();
    void oneStep();

    void changeRandomColor();
    void paintEvent(QPaintEvent *event);

    bool event(QEvent *e);
    void keyPressEvent(QKeyEvent *event);

signals:
    void gameHasOvered();

public slots:
    void on_playButton_clicked();
    void showGameOver();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::GameWidget *ui;
};

#endif // GAMEWIDGET_H


