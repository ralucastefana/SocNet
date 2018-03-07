#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    int command = -1;
    write(client->sd,&command,sizeof(command));
    this->hide();
}

void MainWindow::on_pushButton_clicked()
{
   Login login;
   login.client = this->client;
   login.main = this;
   login.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    Register regist;
    regist.client = this->client;
    regist.main = this;
    regist.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    int command = 0;
    write(client->sd,&command,sizeof(command));
    vector<NewsfeedItem> nf;
    int size;
    read(client->sd,&size,sizeof(size));
    for(int i = 0; i < size; i++)
    {
        NewsfeedItem nfItem;
        read(client->sd,&nfItem,sizeof(nfItem));
        nf.push_back(nfItem);
    }
    if(ui->newsfeedScrollContents->layout() != NULL)
    {
    QLayoutItem *wItem;
    while ((wItem = ui->newsfeedScrollContents->layout()->takeAt(0)) != 0)
        delete wItem->widget();
    delete ui->newsfeedScrollContents->layout();
    }
    QVBoxLayout *layout = new QVBoxLayout();
    for(NewsfeedItem nfItem:nf)
    {
        char *nume = (char *)malloc((size_t) 400);
        strcpy(nume,nfItem.FirstName);
        strcat(nume," ");
        strcat(nume,nfItem.LastName);
        QLabel *title = new QLabel(tr(nume));
        title->setStyleSheet("font-weight: bold");
        QLabel *label = new QLabel(QString(nfItem.Message));
        QLabel *label2 = new QLabel(tr(nfItem.Date));
        layout->addWidget(title);
        layout->addWidget(label);
        layout->addWidget(label2);
    }
    ui->newsfeedScrollContents->setLayout(layout);
}
