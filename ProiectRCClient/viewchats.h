#ifndef VIEWCHATS_H
#define VIEWCHATS_H

#include <QDialog>
#include <client.h>
#include "structs.h"
#include <client.h>
#include "structs.h"
#include <QLabel>
#include <QVBoxLayout>
#include <string.h>
#include <QFrame>
#include <QPushButton>
#include <QAction>
#include <QSignalMapper>
#include <createchat.h>
#include <chat.h>


namespace Ui {
class ViewChats;
}

class ViewChats : public QDialog
{
    Q_OBJECT

public:
    explicit ViewChats(QWidget *parent = 0);
    Client *client;
    void refreshChats();
    ~ViewChats();

private slots:
    void on_pushButton_clicked();

    void viewChat();

    void on_pushButton_2_clicked();

private:
    Ui::ViewChats *ui;
};

#endif // VIEWCHATS_H
