#ifndef HOMEPAGE_H
#define HOMEPAGE_H

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
class Homepage;
}

class Homepage : public QDialog
{
    Q_OBJECT

public:
    explicit Homepage(QWidget *parent = 0);
    ~Homepage();
    Client *client;

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

public slots:
    void deletePost();
    
private:
    Ui::Homepage *ui;
};

#endif // HOMEPAGE_H
