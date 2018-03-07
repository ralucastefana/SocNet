#include "profileedit.h"
#include "ui_profileedit.h"

ProfileEdit::ProfileEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileEdit)
{
    ui->setupUi(this);
}

ProfileEdit::~ProfileEdit()
{
    delete ui;
}

void ProfileEdit::PopulateProfile()
{
    ui->firstname->setText(this->client->user.FirstName);
    ui->lastname->setText(this->client->user.LastName);
    ui->username->setText(this->client->user.UserName);
    ui->password->setText(this->client->user.Password);
    this->client->user.Type==0?ui->user->setChecked(true):ui->admin->setChecked(true);
    this->client->user.Profile==0?ui->public_2->setChecked(true):ui->private_2->setChecked(true);
}

void ProfileEdit::on_pushButton_clicked()
{
    this->hide();
}

void ProfileEdit::on_pushButton_2_clicked()
{
    int command = 3;
    write(client->sd,&command,sizeof(command));
    UserDTO user;
    user.ID = this->client->user.ID;
    strcpy(user.FirstName, ui->firstname->text().toStdString().c_str());
    strcpy(user.LastName, ui->lastname->text().toStdString().c_str());
    strcpy(user.UserName, ui->username->text().toStdString().c_str());
    strcpy(user.Password, ui->password->text().toStdString().c_str());
    user.Type = ui->user->isChecked()?0:1;
    user.Profile = ui->public_2->isChecked()?0:1;
    write(client->sd,&user,sizeof(user));
    this->client->user = user;
    this->hide();
}
