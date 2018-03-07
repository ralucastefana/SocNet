#include "client.h"

Client::Client()
{
    /* umplem structura folosita pentru realizarea conexiunii cu serverul */
    /* familia socket-ului */
    server.sin_family = AF_INET;
    /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* portul de conectare */
    server.sin_port = htons (PORT);
}

void Client::PrepareSocket()
{
    /* cream socketul */
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
      {
        perror ("Eroare la socket().\n");
        throw errno;
      }
}

void Client::ConnectToServer()
{
    /* ne conectam la server */
      if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
        {
          perror ("[client]Eroare la connect().\n");
          throw errno;
        }   
}
