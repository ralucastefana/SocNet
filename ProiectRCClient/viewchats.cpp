#include "viewchats.h"
#include "ui_viewchats.h"

ViewChats::ViewChats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewChats)
{
    ui->setupUi(this);
}

ViewChats::~ViewChats()
{
    delete ui;
}

void ViewChats::on_pushButton_clicked()
{
    this->hide();
}

void ViewChats::refreshChats()
{
    int command = 11, ID = this->client->user.ID;
    write(client->sd,&command,sizeof(command));
    write(client->sd,&ID,sizeof(ID));
    vector<ChatsDTO> chats;
    int size;
    read(client->sd,&size,sizeof(size));
    for(int i = 0; i < size; i++)
    {
        ChatsDTO chatItem;
        read(client->sd,&chatItem,sizeof(chatItem));
        chats.push_back(chatItem);
    }
    if(ui->scrollAreaWidgetContents->layout() !=NULL)
    {
    QLayoutItem *wItem;
    while ((wItem = ui->scrollAreaWidgetContents->layout()->takeAt(0)) != 0)
        delete wItem->widget();
    delete ui->scrollAreaWidgetContents->layout();
    }
    QVBoxLayout *layout = new QVBoxLayout();
    for(ChatsDTO chatItem:chats)
    {
        QLabel *title = new QLabel(tr(chatItem.Names));
        title->setStyleSheet("font-weight: bold");
        layout->addWidget(title);
        QPushButton *unfriendButton = new QPushButton(this);
        unfriendButton->setText("View chat");
        unfriendButton->setProperty("ChatID",chatItem.ChatID);
        QObject::connect(unfriendButton,SIGNAL(clicked()),this,SLOT(viewChat()));
        layout->addWidget(unfriendButton);

    }
    ui->scrollAreaWidgetContents->setLayout(layout);
}

void ViewChats::viewChat()
{
    QVariant propertyV = sender()->property("ChatID");
    if (propertyV.isValid())
    {
        Chat chat;
        chat.ChatID = propertyV.toInt();
        chat.client = this->client;
        chat.RefreshMessages();
        chat.exec();
    }
}

void ViewChats::on_pushButton_2_clicked()
{
    CreateChat chat;
    chat.client = this->client;
    chat.refreshChat();
    chat.viewChats = this;
    chat.exec();
}
