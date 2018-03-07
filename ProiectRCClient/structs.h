#ifndef STRUCTS_H
#define STRUCTS_H


#include <string.h>
#include <array>
#include <sqlite3.h>

using namespace std;

struct thData {
    int idThread;
    int client;
};

struct LoginDTO {
    LoginDTO(const char *username,const char *password) {
        strcpy(this->username,username);
        strcpy(this->password,password);
    }
    LoginDTO(){}
    char username[100];
    char password[100];
};

struct UserDTO{
    int ID;
    char FirstName[100];
    char LastName[100];
    char UserName[100];
    char Password[100];
    int Type;
    int Profile;
    UserDTO(){
        this->ID=0;
    }
    UserDTO(sqlite3_stmt* stmt){
        this->ID = sqlite3_column_int(stmt, 0);
        strcpy(this->FirstName, (const char *) sqlite3_column_text(stmt, 1));
        strcpy(this->LastName, (const char *) sqlite3_column_text(stmt, 2));
        strcpy(this->UserName, (const char *) sqlite3_column_text(stmt, 3));
        strcpy(this->Password, (const char *) sqlite3_column_text(stmt, 4));
        this->Type = sqlite3_column_int(stmt, 5);
        this->Profile = sqlite3_column_int(stmt, 6);
    }
};

struct PostDTO {
    int PostID;
    int UserID;
    char Date[30];
    int Type;
    char Message[500];
};

struct NewsfeedItem:PostDTO
{
    char FirstName[100];
    char LastName[100];
    NewsfeedItem(){}
    NewsfeedItem(sqlite3_stmt* stmt){ //PostID, UserID, FirstName, LastName, Message, Type, Date
        this->PostID = sqlite3_column_int(stmt, 0);
        this->UserID = sqlite3_column_int(stmt, 1);
        strcpy(this->FirstName, (const char *) sqlite3_column_text(stmt, 2));
        strcpy(this->LastName, (const char *) sqlite3_column_text(stmt, 3));
        strcpy(this->Message, (const char *) sqlite3_column_text(stmt, 4));
        this->Type = sqlite3_column_int(stmt, 5);
        strcpy(this->Date, (const char *) sqlite3_column_text(stmt, 6));
    }
};

struct FriendDTO
{
    int FriendID;
    char FirstName[100];
    char LastName[100];
    int Type;
    FriendDTO(){}
    FriendDTO(sqlite3_stmt* stmt)
    {
        this->FriendID = sqlite3_column_int(stmt, 0);
        strcpy(this->FirstName, (const char *) sqlite3_column_text(stmt, 1));
        strcpy(this->LastName, (const char *) sqlite3_column_text(stmt, 2));
        this->Type = sqlite3_column_int(stmt, 3);
    }
};

struct NewFriendDTO
{
    int UserID;
    int FriendID;
    int Type;
};

struct ChatsDTO
{
    int ChatID;
    char Names[300];
    ChatsDTO(){}
    ChatsDTO(sqlite3_stmt* stmt)
    {
        this->ChatID = sqlite3_column_int(stmt, 0);
        strcpy(this->Names, (const char *) sqlite3_column_text(stmt, 1));
    }
};

struct MessageDTO
{
    int ChatID;
    int UserID;
    char FirstName[100];
    char LastName[100];
    char Message[300];
    char Date[30];
    MessageDTO(){}
    MessageDTO(sqlite3_stmt* stmt){
        this->ChatID = sqlite3_column_int(stmt, 0);
        this->UserID = sqlite3_column_int(stmt, 1);
        strcpy(this->FirstName, (const char *) sqlite3_column_text(stmt, 2));
        strcpy(this->LastName, (const char *) sqlite3_column_text(stmt, 3));
        strcpy(this->Message, (const char *) sqlite3_column_text(stmt, 4));
        strcpy(this->Date, (const char *) sqlite3_column_text(stmt, 5));
    }
};


#endif // STRUCTS_H
