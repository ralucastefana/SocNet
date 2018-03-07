#include <iostream>
#include "Server/Server.h"
#include "Database/Database.h"

using namespace std;

static void *treat(void * arg);
void Respond(thData td);
Database db;

int main() {
    Server server;
    pthread_t th[100];
    int i=0;

    server.PrepareSocket();
    server.BindAddress();
    server.ListenForClient();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1)
    {
        int client;
        thData * td; //parametru functia executata de thread
        int length = sizeof (server.from);

        printf ("[server]Asteptam la portul %d...\n",PORT);
        fflush (stdout);

        //client= malloc(sizeof(int));
        /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
        if ((client = accept (server.sd, (struct sockaddr *) &server.from, (socklen_t *) &length)) < 0)
        {
            perror ("[server]Eroare la accept().\n");
            continue;
        }

        /* s-a realizat conexiunea, se astepta mesajul */

        td=(struct thData*)malloc(sizeof(struct thData));
        td->idThread=i++;
        td->client=client;

        pthread_create(&th[i], NULL, &treat, td);

    }
#pragma clang diagnostic pop
}


static void *treat(void * arg)
{
    fflush (stdout);
    pthread_detach(pthread_self());
    thData td=*((struct thData*)arg);
    Respond(td);
    printf("a ajuns in treat close \n");
    // am terminat cu acest client, inchidem conexiunea
    close ( td.idThread);
    return(NULL);
};

void Respond(thData td)
{
    int command;
    while(1)
    {
        read(td.client, &command, sizeof(command));
        printf("[server]: command=%i\n",command);
        switch(command){
            case 0: // public newsfeed
            {
                vector<NewsfeedItem> nf = db.GetNewsfeed();
                int size = (int) nf.size();
                write(td.client,&size,sizeof(size));
                for(NewsfeedItem nfItem:nf)
                    write(td.client,&nfItem,sizeof(nfItem));
                break;
            }
            case 1: //login
            {
                LoginDTO login;
                read(td.client, &login, sizeof(login));
                UserDTO user = db.Login(login);
                write(td.client, &user, sizeof(user));
                break;
            }
            case 2: //register
            {
                UserDTO regist;
                read(td.client, &regist, sizeof(regist));
                UserDTO user = db.Register(regist);
                write(td.client, &user, sizeof(user));
                break;
            }
            case 3: // update user
            {
                UserDTO user;
                read(td.client,&user,sizeof(user));
                db.Update(user);
                break;
            }
            case 4: // insert post
            {
                PostDTO post;
                read(td.client,&post,sizeof(post));
                db.InsertPost(post);
                break;
            }
            case 5: // newsfeed after login
            {
                int ID;
                read(td.client,&ID,sizeof(ID));
                vector<NewsfeedItem> nf = db.GetNewsfeed(ID);
                int size = (int) nf.size();
                write(td.client,&size,sizeof(size));
                for(NewsfeedItem nfItem : nf)
                    write(td.client,&nfItem,sizeof(nfItem));
                break;
            }
            case 6: // delete post
            {
                int postID;
                read(td.client,&postID,sizeof(postID));
                db.Delete(postID);
                break;
            }
            case 7: // refresh friends list
            {
                int userID;
                read(td.client,&userID,sizeof(userID));
                vector<FriendDTO> fr = db.GetFriends(userID);
                int size = (int) fr.size();
                write(td.client,&size,sizeof(size));
                for(FriendDTO frItem : fr)
                    write(td.client,&frItem,sizeof(frItem));
                break;
            }
            case 8: // unfriend
            {
                NewFriendDTO unfriend;
                read(td.client, &unfriend, sizeof(unfriend));
                db.Unfriend(unfriend);
                int finished = 1;
                write(td.client,&finished,sizeof(finished));
                break;
            }
            case 9: //add friend
            {
                NewFriendDTO newFriend;
                read(td.client, &newFriend, sizeof(newFriend));
                db.AddFriend(newFriend);
                int finished = 1;
                write(td.client,&finished,sizeof(finished));
                break;
            }
            case 10: // not my friends
            {
                int userID;
                read(td.client,&userID,sizeof(userID));
                vector<FriendDTO> fr = db.GetNotFriends(userID);
                int size = (int) fr.size();
                write(td.client,&size,sizeof(size));
                for(FriendDTO frItem : fr)
                    write(td.client,&frItem,sizeof(frItem));
                break;
            }
            case 11: // view chats
            {
                int userID;
                read(td.client,&userID,sizeof(userID));
                vector<ChatsDTO> chat = db.GetChats(userID);
                int size = (int) chat.size();
                write(td.client,&size,sizeof(size));
                for(ChatsDTO chatItem : chat)
                    write(td.client,&chatItem,sizeof(chatItem));
                break;
            }
            case 12: // create new chat
            {
                vector<int> usersID;
                int size;
                read(td.client,&size,sizeof(size));
                for(int i=0; i<size; i++)
                {
                    int userID;
                    read(td.client,&userID,sizeof(userID));
                    usersID.push_back(userID);
                }
                db.CreateNewChat(usersID);
                int finished = 1;
                write(td.client,&finished,sizeof(finished));
                break;
            }
            case 13: // insert message
            {
                MessageDTO message;
                read(td.client,&message,sizeof(message));
                db.InsertMessage(message);
                int finished = 1;
                write(td.client,&finished,sizeof(finished));
                break;
            }
            case 14: // get messages
            {
                int ID;
                read(td.client,&ID,sizeof(ID));
                vector<MessageDTO> ms = db.GetMessage(ID);
                int size = (int) ms.size();
                write(td.client,&size,sizeof(size));
                for(MessageDTO message : ms)
                    write(td.client,&message,sizeof(message));
                break;
            }
            default: {
                command = -1;
                break;
            }
        }
        if(command == -1)
        {
            close ( td.idThread);
            break;
        }
        command = -1;
    }
}
