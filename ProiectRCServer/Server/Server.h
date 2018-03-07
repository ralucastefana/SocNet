//
// Created by aby on 05.01.2017.
//

#ifndef PROIECTRCSERVER_SERVER_H
#define PROIECTRCSERVER_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "../Structs/Structs.h"

/* portul folosit */
#define PORT 2908

class Server{
public:
    Server()
    {
        /* pregatirea structurilor de date */
        bzero (&server, sizeof (server));
        bzero (&from, sizeof (from));

        server.sin_family = AF_INET; // stabilirea familiei de socket-uri
        server.sin_addr.s_addr = htonl (INADDR_ANY); // acceptam orice adresa
        server.sin_port = htons (PORT);// utilizam un port utilizator
    }
    struct sockaddr_in server; // structura folosita de server
    struct sockaddr_in from;
    int sd;		//descriptorul de socket
    void PrepareSocket();
    void BindAddress();
    void ListenForClient();
};

#endif //PROIECTRCSERVER_SERVER_H
