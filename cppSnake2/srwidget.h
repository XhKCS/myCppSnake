#ifndef SRWIDGET_H
#define SRWIDGET_H

#include <QWidget>

namespace Ui {
class SRWidget;
}

class Record {
public:
    int playTime;
    int score;
    char name[30];

    Record(int playTime, int score, char name[])
        :playTime(playTime), score(score) {
        strcpy(this->name, name);
    };
};


class SRWidget : public QWidget
{
    Q_OBJECT
protected:
    char* filename;
    std::vector<Record> records;
    QWidget *backWidget;
public:
    explicit SRWidget(QWidget *backWidget, char * filename = "records.txt", QWidget *parent = nullptr);
    ~SRWidget();

    void paintEvent(QPaintEvent *event);


private slots:
    void on_pushButton_clicked();

private:
    Ui::SRWidget *ui;
};

#endif // SRWIDGET_H
