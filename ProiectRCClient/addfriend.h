#ifndef ADDFRIEND_H
#define ADDFRIEND_H

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
#include <friend.h>

namespace Ui {
class AddFriend;
}

class AddFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = 0);
    Client *client;
    class Friend *friendPage;
     void refreshPeople();
    ~AddFriend();

private slots:
    void on_pushButton_clicked();

    void addPeople();

private:
    Ui::AddFriend *ui;
};

#endif // ADDFRIEND_H
