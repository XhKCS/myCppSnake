#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//游戏一开始的主界面

#include <QMainWindow>
//#include "gamewidget.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    bool musicPaused = false;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);
//    void musicPlayOrPause();

private slots:
    void on_startButton_clicked();

//    void on_descripButton_clicked();

    void on_showRecordButton_clicked();

    void on_exitButton_clicked();

    void on_musicButton_clicked();

private:
    Ui::MainWindow *ui;
//    GameWidget *gameWidget;
};
#endif // MAINWINDOW_H
