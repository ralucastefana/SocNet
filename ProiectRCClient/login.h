#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

#include "homepage.h"
#include "structs.h"
#include "client.h"
#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    Client *client;
    QMainWindow *main;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
