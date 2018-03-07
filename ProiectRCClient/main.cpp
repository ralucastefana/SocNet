#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    
    Client client;
    
    client.PrepareSocket();
    client.ConnectToServer();
    
    w.client = &client;
    w.show();

    return a.exec();
}
