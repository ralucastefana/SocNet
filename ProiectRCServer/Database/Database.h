//
// Created by aby on 06.01.2017.
//

#ifndef PROIECTRCSERVER_DATABASE_H
#define PROIECTRCSERVER_DATABASE_H

#include "../Structs/Structs.h"
#include <vector>

class Database{
private:
    sqlite3 *db;
    sqlite3_stmt * stmt;
    char *zErrMsg = 0;
    int rc;
public:
    Database();
    UserDTO Login(LoginDTO user);
    UserDTO Register(UserDTO user);
    void Update(UserDTO user);
    void InsertPost(PostDTO post);
    vector<NewsfeedItem> GetNewsfeed(int ID=0);
    void Delete(int postID);
    vector<FriendDTO> GetFriends(int ID);
    void Unfriend(NewFriendDTO user);
    void AddFriend(NewFriendDTO user);
    vector<FriendDTO> GetNotFriends(int ID);
    vector<ChatsDTO> GetChats(int userID);
    void CreateNewChat(vector <int> users);
    void InsertMessage(MessageDTO message);
    vector<MessageDTO> GetMessage(int chatID);
    ~Database();
};

#endif //PROIECTRCSERVER_DATABASE_H
