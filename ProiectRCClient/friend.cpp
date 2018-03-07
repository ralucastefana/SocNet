#include "friend.h"
#include "ui_friend.h"

Friend::Friend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Friend)
{
    ui->setupUi(this);
}

Friend::~Friend()
{
    delete ui;
}

void Friend::on_pushButton_clicked()
{
    this->hide();
}

void Friend::refreshFriends()
{
    int command = 7, ID = this->client->user.ID;
    write(client->sd,&command,sizeof(command));
    write(client->sd,&ID,sizeof(ID));
    vector<FriendDTO> fr;
    int size;
    read(client->sd,&size,sizeof(size));
    for(int i = 0; i < size; i++)
    {
        FriendDTO frItem;
        read(client->sd,&frItem,sizeof(frItem));
        fr.push_back(frItem);
    }
    if(ui->friendScrollContents->layout() !=NULL)
    {
    QLayoutItem *wItem;
    while ((wItem = ui->friendScrollContents->layout()->takeAt(0)) != 0)
        delete wItem->widget();
    delete ui->friendScrollContents->layout();
    }
    QVBoxLayout *layout = new QVBoxLayout();
    for(FriendDTO frItem:fr)
    {
        char *nume = (char *)malloc((size_t) 400);
        strcpy(nume,frItem.FirstName);
        strcat(nume," ");
        strcat(nume,frItem.LastName);
        QLabel *title = new QLabel(tr(nume));
        title->setStyleSheet("font-weight: bold");
        QLabel *label = new QLabel(tr(frItem.Type==0?"Friend":"Close friend"));
        layout->addWidget(title);
        layout->addWidget(label);
        QPushButton *unfriendButton = new QPushButton(this);
        unfriendButton->setText("Unfriend");
        unfriendButton->setProperty("FriendID",frItem.FriendID);
        QObject::connect(unfriendButton,SIGNAL(clicked()),this,SLOT(unfriend()));
        layout->addWidget(unfriendButton);

    }
    ui->friendScrollContents->setLayout(layout);
}

void Friend::unfriend()
{
    QVariant propertyV = sender()->property("FriendID");
    if (propertyV.isValid())
    {
        NewFriendDTO unfriend;
        unfriend.UserID = this->client->user.ID;
        unfriend.FriendID = propertyV.toInt();
        unfriend.Type = 0;
        int command = 8;
        write(client->sd,&command,sizeof(command));
        write(client->sd,&unfriend,sizeof(unfriend));
        int finished;
        read(client->sd,&finished,sizeof(finished));
        refreshFriends(); // update la lista cu prieteni
    }
}

void Friend::on_pushButton_2_clicked()
{
    AddFriend fr;
    fr.client = this->client;
    fr.friendPage = this;
    fr.refreshPeople();
    fr.exec();
}
