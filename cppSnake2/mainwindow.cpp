#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "gamewidget.h"
#include "srwidget.h"
#include "sdwidget.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->player = new QMediaPlayer(this);
    this->playlist = new QMediaPlaylist(player);

//    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    //用相对路径
    playlist->addMedia(QUrl::fromLocalFile("weibaizhen.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("zhenxinzhen.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop); //循环播放

//    player->setMedia(QUrl::fromLocalFile("weibaizhen.mp3"));
    // 连接player与playlist
    player->setPlaylist(playlist);
    player->setVolume(10); //0~100音量范围,默认是100
    player->play();

    //联系音量条与播放器
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(player->volume());

    connect(player, &QMediaPlayer::volumeChanged, [=](){
        ui->volumeSlider->setValue(player->volume());
        if (player->volume()==0) {
            QPixmap pixmap(":/res/silence.jpg");
            ui->musicButton->setIcon(QIcon(pixmap));
            ui->musicButton->setIconSize(ui->musicButton->size());
        }
        else {
            QPixmap pixmap(":/res/voice.jpg");
            ui->musicButton->setIcon(QIcon(pixmap));
            ui->musicButton->setIconSize(ui->musicButton->size());
        }
    });
    connect(ui->volumeSlider, &QSlider::valueChanged, [=]() {
        player->setVolume(ui->volumeSlider->value());
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
}

//void MainWindow::musicPlayOrPause() //不用暂停，只要调音量
//{
//    if (this->player->state()==QMediaPlayer::PausedState) {
//        player->play();
//        QPixmap pixmap(":/res/voice.jpg");
//        ui->musicButton->setIcon(QIcon(pixmap));
//        ui->musicButton->setIconSize(ui->musicButton->size());
//    }
//}


void MainWindow::on_startButton_clicked()
{
//    qDebug() << "游戏开始！";
    //打开游戏窗口GameWidget；主页面隐藏
    //应该先弹出单选框页面选难度
    SDWidget *sdWidget = new SDWidget(this, nullptr);
    sdWidget->show();
//    GameWidget *game = new GameWidget(this, nullptr, 1);
//    game->show();
//    this->setVisible(false);
    this->showMinimized();

}


//void MainWindow::on_descripButton_clicked()
//{
//    //打开项目说明窗口
//}


void MainWindow::on_showRecordButton_clicked()
{
     //打开积分记录页面（传文件名）
    SRWidget *sRWidget = new SRWidget(this, "records.txt", nullptr);
    sRWidget->show();
    this->showMinimized();
}


void MainWindow::on_exitButton_clicked()
{
//    qDebug() << "游戏结束！";
    //先打开标准对话询问窗口询问是否真的要关闭游戏
    int v = QMessageBox::question(this, "询问", "确认要退出吗？", QMessageBox::Yes|QMessageBox::No);
    if (v == QMessageBox::Yes) {
        QMessageBox::information(this, "再见界面", "程序将退出，欢迎下次使用！");
        this->close();
    }
}


void MainWindow::on_musicButton_clicked()
{
    if (player->volume() != 0) {
        player->setVolume(0);
    }
    else {
        player->setVolume(20);
    }
}

