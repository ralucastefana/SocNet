#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_pushButton_2_clicked()
{
    this->hide();
}

void Chat::on_pushButton_clicked()
{

    MessageDTO message;
    int command = 13;
    write(client->sd,&command,sizeof(command));
    message.ChatID = this->ChatID;
    message.UserID = this->client->user.ID;
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (message.Date,30,"%F %T",timeinfo);
    strcpy(message.Message,ui->textEdit->toPlainText().toStdString().c_str());
    write(client->sd,&message,sizeof(message));
    int finished;
    read(client->sd,&finished,sizeof(finished));
    RefreshMessages();
    ui->textEdit->setText("");
}

void Chat::RefreshMessages()
{
    int chatID = this->ChatID, command = 14;
    write(client->sd,&command,sizeof(command));
    write(client->sd,&chatID,sizeof(chatID));
    vector<MessageDTO> ms;
    int size;
    read(client->sd,&size,sizeof(size));
    for(int i = 0; i < size; i++)
    {
        MessageDTO message;
        read(client->sd,&message,sizeof(message));
        ms.push_back(message);
    }
    if(ui->scrollAreaWidgetContents->layout() !=NULL)
    {
    QLayoutItem *wItem;
    while ((wItem = ui->scrollAreaWidgetContents->layout()->takeAt(0)) != 0)
        delete wItem->widget();
    delete ui->scrollAreaWidgetContents->layout();
    }

    QVBoxLayout *layout = new QVBoxLayout();
    for(MessageDTO message:ms)
    {
        char *nume = (char *)malloc((size_t) 400);
        strcpy(nume,message.FirstName);
        strcat(nume," ");
        strcat(nume,message.LastName);
        QLabel *title = new QLabel(tr(nume));
        title->setStyleSheet("font-weight: bold");
        QLabel *label = new QLabel(message.Message);
        QLabel *label2 = new QLabel(tr(message.Date));
        layout->addWidget(title);
        layout->addWidget(label);
        layout->addWidget(label2);
    }
    ui->scrollAreaWidgetContents->setLayout(layout);
}
