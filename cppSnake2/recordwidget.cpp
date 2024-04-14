#include "recordwidget.h"
#include "ui_recordwidget.h"
#include <cstdio>
#include <cstdlib>
#include <QMessageBox>
#include <QPainter>

RecordWidget::RecordWidget(QWidget *backWidget, int playTime, int score, const char *path, QWidget *parent) :
    QWidget(parent), playTime(playTime), score(score), backWidget(backWidget),
    ui(new Ui::RecordWidget)
{
    ui->setupUi(this);
    //别忘记先动态分配内存
    this->path = new char[strlen(path)+1];
    strcpy(this->path, path);
//    this->setAttribute(Qt::WA_DeleteOnClose);
}

RecordWidget::~RecordWidget()
{
    delete ui;
}

void RecordWidget::on_confirmBtn_clicked()
{
    QString name = ui->nameInput->text();
    //打开文件并加入数据，再关闭
    FILE *fp = fopen(path, "a+");
    fprintf(fp, "%d\t\t  %d\t\t %s \n", playTime, score, name.toUtf8().data());
    fclose(fp);

    //弹出提示对话框提示保存成功，之后该窗口close自毁
    int v = QMessageBox::information(this, "提示保存成功", "您的记录已保存成功！");
    this->close();
    backWidget->showNormal();
}


void RecordWidget::on_cancelBtn_clicked()
{
    //弹出询问对话框询问是否取消保存
    int v = QMessageBox::question(this, "询问", "确认要取消保存记录吗？", QMessageBox::Yes|QMessageBox::No);

    if (v == QMessageBox::Yes) {
        this->close();
        backWidget->showNormal();
    }
}

void RecordWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/bg2.png"));
}

