#include "addfriend.h"
#include "ui_addfriend.h"

AddFriend::AddFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::on_pushButton_clicked()
{
    this->hide();
    this->friendPage->refreshFriends();
}

void AddFriend::refreshPeople()
{
    int command = 10, ID = this->client->user.ID;
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
    if(ui->addFriendScrollAreaContents->layout() !=NULL) // verificam daca exista in layout si stergem
    {
    QLayoutItem *wItem;
    while ((wItem = ui->addFriendScrollAreaContents->layout()->takeAt(0)) != 0)
        delete wItem->widget();
    delete ui->addFriendScrollAreaContents->layout();
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
        layout->addWidget(title);

        QPushButton *friendButton = new QPushButton(this);
        friendButton->setText("Add as friend");
        friendButton->setProperty("FriendID",frItem.FriendID);
        friendButton->setProperty("Type",0);
        QPushButton *closefriendButton = new QPushButton(this);
        closefriendButton->setText("Add as close friend");
        closefriendButton->setProperty("FriendID",frItem.FriendID);
        closefriendButton->setProperty("Type",1);

        QObject::connect(friendButton,SIGNAL(clicked()),this,SLOT(addPeople()));
        layout->addWidget(friendButton);
        QObject::connect(closefriendButton,SIGNAL(clicked()),this,SLOT(addPeople()));
        layout->addWidget(closefriendButton);


    }
    ui->addFriendScrollAreaContents->setLayout(layout);
}


void AddFriend::addPeople()
{
    QVariant propertyV = sender()->property("FriendID");
    if (propertyV.isValid())
    {
        NewFriendDTO unfriend;
        unfriend.UserID = this->client->user.ID;
        unfriend.FriendID = propertyV.toInt();
        unfriend.Type = sender()->property("Type").toInt();
        int command = 9;
        write(client->sd,&command,sizeof(command));
        write(client->sd,&unfriend,sizeof(unfriend));
        int finished;
        read(client->sd,&finished,sizeof(finished));
        refreshPeople(); // update la lista cu prieteni
    }

}
