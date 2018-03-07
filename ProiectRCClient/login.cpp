#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
     QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_2_clicked()
{
    this->hide();

}

void Login::on_pushButton_clicked()
{
    int command = 1;
    write(client->sd,&command,sizeof(command));
    LoginDTO login = LoginDTO(ui->username->text().toStdString().c_str(),ui->password->text().toStdString().c_str());
    write(client->sd,&login,sizeof(login));
    UserDTO user;
    read(client->sd,&user,sizeof(user));
    if(user.ID != 0)
    {
        this->hide();
        this->main->hide();
        Homepage home;
        this->client->user=user;
        home.client = this->client;
        home.exec();
    }
    else
    {
        ui->loginerror->setText("Login Error");
    }
}
