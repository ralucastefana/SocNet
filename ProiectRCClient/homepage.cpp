#include "homepage.h"
#include "ui_homepage.h"

Homepage::Homepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Homepage)
{
    ui->setupUi(this);
}

Homepage::~Homepage()
{
    delete ui;
}

void Homepage::on_pushButton_5_clicked()
{
    int command = -1;
    write(client->sd,&command,sizeof(command));
    this->hide();
}

void Homepage::on_pushButton_4_clicked()
{
    ProfileEdit profileEdit;
    profileEdit.client = this->client;
    profileEdit.PopulateProfile();
    profileEdit.exec();
}

void Homepage::on_pushButton_6_clicked()
{
    PostDTO post;
    int command = 4;
    write(client->sd,&command,sizeof(command));
    post.UserID = this->client->user.ID;
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (post.Date,30,"%F %T",timeinfo);
    post.Type = ui->public_2->isChecked()?0:ui->friends->isChecked()?1:2;
    strcpy(post.Message,ui->post->toPlainText().toStdString().c_str());
    write(client->sd,&post,sizeof(post));
    ui->post->setText("");
}

void Homepage::on_pushButton_clicked()
{
    int ID = this->client->user.ID, command = 5;
    write(client->sd,&command,sizeof(command));
    write(client->sd,&ID,sizeof(ID));
    vector<NewsfeedItem> nf;
    int size;
    read(client->sd,&size,sizeof(size));
    for(int i = 0; i < size; i++)
    {
        NewsfeedItem nfItem;
        read(client->sd,&nfItem,sizeof(nfItem));
        nf.push_back(nfItem);
    }
    if(ui->newsfeedScrollContents->layout() !=NULL)
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
        QLabel *label = new QLabel(nfItem.Message);
        QLabel *label2 = new QLabel(tr(nfItem.Date));
        layout->addWidget(title);
        layout->addWidget(label);
        layout->addWidget(label2);
        if(this->client->user.Type == 1 || this->client->user.ID == nfItem.UserID)
        {
            QPushButton *deleteButton = new QPushButton(this);
            deleteButton->setText("Delete Post");
            deleteButton->setProperty("postID",nfItem.PostID);
            QObject::connect(deleteButton,SIGNAL(clicked()),this,SLOT(deletePost()));
            layout->addWidget(deleteButton);

        }
    }
    ui->newsfeedScrollContents->setLayout(layout);
}

void Homepage::deletePost()
{
    QVariant propertyV = sender()->property("postID");
    if (propertyV.isValid())
    {
        int postID = propertyV.toInt();
        int command = 6;
        write(client->sd,&command,sizeof(command));
        write(client->sd,&postID,sizeof(postID));
        on_pushButton_clicked(); // update la newsfeed
    }
}

void Homepage::on_pushButton_2_clicked()
{
    Friend fr;
    fr.client = this->client;
    fr.refreshFriends();
    fr.exec();
}

void Homepage::on_pushButton_3_clicked()
{
    ViewChats chats;
    chats.client = this->client;
    chats.refreshChats();
    chats.exec();
}
