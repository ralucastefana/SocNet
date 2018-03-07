#ifndef FRIEND_H
#define FRIEND_H

#include <QDialog>
#include <client.h>
#include "structs.h"
#include <QLabel>
#include <QVBoxLayout>
#include <string.h>
#include <QFrame>
#include <QPushButton>
#include <QAction>
#include <QSignalMapper>
#include<addfriend.h>


namespace Ui {
class Friend;
}

class Friend : public QDialog
{
    Q_OBJECT

public:
    explicit Friend(QWidget *parent = 0);
    Client *client;
    void refreshFriends();
    ~Friend();

private slots:
    void on_pushButton_clicked();

    void unfriend();

    void on_pushButton_2_clicked();

private:
    Ui::Friend *ui;
};

#endif // FRIEND_H
