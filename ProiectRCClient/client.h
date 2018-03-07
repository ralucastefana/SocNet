#ifndef CLIENT_H
#define CLIENT_H

#include "structs.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <cstddef>

#define PORT 2908  //  portul de conectare la server
class Client
{
public:
    Client();
    int sd;			// descriptorul de socket
    struct sockaddr_in server;	// structura folosita pentru conectare
    void PrepareSocket();
    void ConnectToServer();
    UserDTO user;

};

#endif // CLIENT_H
