#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_2_clicked()
{
    this->hide();
}


void Register::on_pushButton_clicked()
{
    int command = 2;
    write(client->sd,&command,sizeof(command));
    UserDTO user;
    strcpy(user.FirstName, ui->firstname->text().toStdString().c_str());
    strcpy(user.LastName, ui->lastname->text().toStdString().c_str());
    strcpy(user.UserName, ui->username->text().toStdString().c_str());
    strcpy(user.Password, ui->password->text().toStdString().c_str());
    user.Type = ui->user->isChecked()?0:1;
    user.Profile = ui->public_2->isChecked()?0:1;
    write(client->sd,&user,sizeof(user));
    read(client->sd,&user,sizeof(user));
    if(user.ID != 0)
    {
        this->hide();
        this->main->hide();
        this->client->user = user;
        Homepage home;
        home.client = this->client;
        home.exec();
    }
    else
        ui->registererror->setText("Register Error");
}
