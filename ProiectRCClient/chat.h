#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <client.h>
#include "profileedit.h"
#include "structs.h"
#include <time.h>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <string.h>
#include <QFrame>
#include <QPushButton>
#include <QAction>
#include <QSignalMapper>
#include <friend.h>
#include <viewchats.h>

namespace Ui {
class Chat;
}

class Chat : public QDialog
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    Client *client;
    int ChatID;
    void RefreshMessages();
    ~Chat();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Chat *ui;
};

#endif // CHAT_H
