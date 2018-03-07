#include "createchat.h"
#include "ui_createchat.h"

CreateChat::CreateChat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateChat)
{
    ui->setupUi(this);
}

CreateChat::~CreateChat()
{
    delete ui;
}

void CreateChat::on_pushButton_clicked()
{
     this->hide();
}

void CreateChat::refreshChat()
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
    if(ui->scrollAreaWidgetContents->layout() !=NULL) // verificam daca exista in layout si stergem
    {
    QLayoutItem *wItem;
    while ((wItem = ui->scrollAreaWidgetContents->layout()->takeAt(0)) != 0)
        delete wItem->widget();
    delete ui->scrollAreaWidgetContents->layout();
    }
    QVBoxLayout *layout = new QVBoxLayout();
    for(FriendDTO frItem:fr)
    {
        char *nume = (char *)malloc((size_t) 400);
        strcpy(nume,frItem.FirstName);
        strcat(nume," ");
        strcat(nume,frItem.LastName);

        QCheckBox *friendButton = new QCheckBox(this);
        friendButton->setText(nume);
        friendButton->setProperty("FriendID",frItem.FriendID);
        layout->addWidget(friendButton);

    }
    ui->scrollAreaWidgetContents->setLayout(layout);
}

void CreateChat::on_pushButton_2_clicked()
{
    vector<int> usersID;
    for (int i = 0; i < ui->scrollAreaWidgetContents->layout()->count(); ++i)
    {
      QCheckBox *widget = qobject_cast<QCheckBox*> (ui->scrollAreaWidgetContents->layout()->itemAt(i)->widget());
      if (widget != NULL && widget->checkState() == Qt::Checked)
      {
        usersID.push_back(widget->property("FriendID").toInt());
      }
    }
    if(usersID.size()!=0){
        usersID.push_back(this->client->user.ID);
        int command = 12;
        write(client->sd,&command,sizeof(command));
        int size = usersID.size() ;
        write(client->sd,&size,sizeof(size));
        for(int userID : usersID)
            write(client->sd,&userID,sizeof(userID));

        int finished;
        read(client->sd,&finished,sizeof(finished));
    }
    this->viewChats->refreshChats();
    on_pushButton_clicked();

}
