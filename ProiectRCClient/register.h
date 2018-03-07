#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

#include "homepage.h"
#include "structs.h"
#include "client.h"
#include <QMainWindow>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();
    Client *client;
    QMainWindow *main;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
