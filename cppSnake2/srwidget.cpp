#include "srwidget.h"
#include "ui_srwidget.h"
#include <QPainter>

SRWidget::SRWidget(QWidget * backWidget, char * filename, QWidget *parent) :
    QWidget(parent),
    backWidget(backWidget),
    ui(new Ui::SRWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //不可修改


    FILE *fp = fopen(filename, "r");
    char buff[255];
    fgets(buff, 255, fp); //跳过第一行
    int playTime, score;
    char name[30];
    int maxScore = 0;

    records.reserve(20);
    while (fscanf(fp, "%d %d %s", &playTime, &score, name) != EOF)
    {
        if (score>maxScore) maxScore = score;
        Record record(playTime, score, name);
        this->records.push_back(record);
    }
    fclose(fp);

    //设置行数和列数
    int rows = records.size();
    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(3);
    //设置表头标题
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"游戏时长（秒）"<<"得分"<<"玩家姓名");
    //添加数据
    for (int i = 0; i < rows; ++i)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(records[i].playTime)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(records[i].score)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString(records[i].name)));
    }
    QString str = QString("当前最高分记录：%1分").arg(maxScore);
    ui->hrLabel->setText(str);

}

SRWidget::~SRWidget()
{
    delete ui;
}

void SRWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/res/bg3.jpg"));
}

void SRWidget::on_pushButton_clicked()
{
    backWidget->showNormal();
    this->close();

}

