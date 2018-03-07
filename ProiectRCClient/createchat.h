#ifndef CREATECHAT_H
#define CREATECHAT_H

#include <QDialog>
#include <client.h>
#include "structs.h"
#include <QLabel>
#include <QVBoxLayout>
#include <string.h>
#include <QFrame>
#include <QCheckBox>
#include <QAction>
#include <QSignalMapper>
#include <viewchats.h>

namespace Ui {
class CreateChat;
}

class CreateChat : public QDialog
{
    Q_OBJECT

public:
    explicit CreateChat(QWidget *parent = 0);
    Client *client;
    class ViewChats *viewChats;
    void refreshChat();
    ~CreateChat();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CreateChat *ui;
};

#endif // CREATECHAT_H
