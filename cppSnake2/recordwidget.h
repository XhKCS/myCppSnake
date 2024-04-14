#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>

namespace Ui {
class RecordWidget;
}

class RecordWidget : public QWidget
{
    Q_OBJECT
protected:
    int playTime;
    int score;
    char *path;
    QWidget *backWidget;
public:
    explicit RecordWidget(QWidget *backWidget, int playTime, int score, const char *path = "records.txt", QWidget *parent = nullptr);
    ~RecordWidget();

private slots:
    void on_confirmBtn_clicked();

    void on_cancelBtn_clicked();

    void paintEvent(QPaintEvent *event);

private:
    Ui::RecordWidget *ui;
};

#endif // RECORDWIDGET_H
