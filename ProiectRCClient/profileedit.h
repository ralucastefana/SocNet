#ifndef PROFILEEDIT_H
#define PROFILEEDIT_H

#include <QDialog>
#include "client.h"

namespace Ui {
class ProfileEdit;
}

class ProfileEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileEdit(QWidget *parent = 0);
    ~ProfileEdit();
    Client *client;
    void PopulateProfile();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ProfileEdit *ui;
};

#endif // PROFILEEDIT_H
