//
// Created by aby on 06.01.2017.
//

#include <stdio.h>
#include "Database.h"

Database::Database() {
    rc = sqlite3_open("VirtualSoc.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        throw "SqlException"; //arunca eroare cand nu se realizeaza conexiunea
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
}

Database::~Database() {
    sqlite3_close(db);
}

UserDTO Database::Register(UserDTO user) {
    char *sqlQuery = (char *)malloc((size_t) 300);
    strcpy(sqlQuery,"INSERT INTO users (FirstName, LastName, UserName, Password, Type, Profile) VALUES ('");
    strcat(sqlQuery,user.FirstName);
    strcat(sqlQuery,"' , '");
    strcat(sqlQuery,user.LastName);
    strcat(sqlQuery,"' , '");
    strcat(sqlQuery,user.UserName);
    strcat(sqlQuery,"' , '");
    strcat(sqlQuery,user.Password);
    strcat(sqlQuery,"' , ");
    strcat(sqlQuery, to_string(user.Type).c_str());
    strcat(sqlQuery," , ");
    strcat(sqlQuery, to_string(user.Profile).c_str());
    strcat(sqlQuery,")");
    rc = sqlite3_exec(db, sqlQuery, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    return Login(LoginDTO(user.UserName,user.Password));
}

UserDTO Database::Login(LoginDTO loginUser) {
    char *sqlQuery = (char *)malloc((size_t) 200);
    strcpy(sqlQuery,"SELECT * from Users where UserName = '");
    strcat(sqlQuery,loginUser.username);
    strcat(sqlQuery,"' and Password = '");
    strcat(sqlQuery,loginUser.password);
    strcat(sqlQuery,"' ");
    rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, 0);//preparing the statement
    if (rc != SQLITE_OK) {

        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw "SqlException";
    }
    UserDTO user;
    if ((rc = sqlite3_step(stmt) == SQLITE_ROW)) //executing the statement
        user = UserDTO(stmt);
    return user;
}

void Database::Update(UserDTO user) {
    char *sqlQuery = (char *)malloc((size_t) 300);
    strcpy(sqlQuery,"UPDATE users set FirstName = '");
    strcat(sqlQuery,user.FirstName);
    strcat(sqlQuery,"' , LastName =  '");
    strcat(sqlQuery,user.LastName);
    strcat(sqlQuery,"' , UserName =  '");
    strcat(sqlQuery,user.UserName);
    strcat(sqlQuery,"' , Password =  '");
    strcat(sqlQuery,user.Password);
    strcat(sqlQuery,"' , Type =  ");
    strcat(sqlQuery, to_string(user.Type).c_str());
    strcat(sqlQuery," , Profile = ");
    strcat(sqlQuery, to_string(user.Profile).c_str());
    strcat(sqlQuery," where ID = ");
    strcat(sqlQuery, to_string(user.ID).c_str());
    rc = sqlite3_exec(db, sqlQuery, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records updated successfully\n");
    }
}

void Database::InsertPost(PostDTO post) {
    char *sqlQuery = (char *)malloc((size_t) 300);
    strcpy(sqlQuery,"INSERT INTO posts (UserID, Date, Type, Message) VALUES (");
    strcat(sqlQuery,to_string(post.UserID).c_str());
    strcat(sqlQuery," , '");
    strcat(sqlQuery,post.Date);
    strcat(sqlQuery,"' , ");
    strcat(sqlQuery,to_string(post.Type).c_str());
    strcat(sqlQuery," , '");
    strcat(sqlQuery,post.Message);
    strcat(sqlQuery,"' ) ");
    rc = sqlite3_exec(db, sqlQuery, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
}

vector<NewsfeedItem> Database::GetNewsfeed(int ID) {
    char *sqlQuery = (char *)malloc((size_t) 400);
    strcpy(sqlQuery,"SELECT PostID, UserID, FirstName, LastName, Message, p.Type, Date from posts p left join users u on p.UserID = u.ID where p.Type = 0 ");
    if(ID>0)
    {
        strcat(sqlQuery," or (p.Type = 1 and exists (SELECT * from friends f where f.UserID = p.UserID and f.FriendID = " );
        strcat(sqlQuery,to_string(ID).c_str());
        strcat(sqlQuery," and p.Type >= 1)) or (p.Type = 1 and exists (SELECT * from friends f where f.UserID = p.UserID and f.FriendID =  ");
        strcat(sqlQuery,to_string(ID).c_str());
        strcat(sqlQuery," and p.Type >= 2)) or (p.UserID = ");
        strcat(sqlQuery,to_string(ID).c_str());
        strcat(sqlQuery," ) ");
    }
    strcat(sqlQuery, " order by Date desc ");
    rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, 0);//preparing the statement
    if (rc != SQLITE_OK) {

        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw "SqlException";
    }
    vector<NewsfeedItem> nf;
    while ((rc = sqlite3_step(stmt) == SQLITE_ROW)) //executing the statement
        nf.push_back(NewsfeedItem(stmt));
    return nf;
}

void Database::Delete(int postID) {
    char *sqlQuery = (char *)malloc((size_t) 300);
    strcpy(sqlQuery,"DELETE from posts where PostID = ");
    strcat(sqlQuery,to_string(postID).c_str());
    rc = sqlite3_exec(db, sqlQuery, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records deleted successfully\n");
    }
}

vector<FriendDTO> Database::GetFriends(int ID) {
    char *sqlQuery = (char *)malloc((size_t) 400);
    strcpy(sqlQuery,"SELECT FriendID, FirstName, LastName, f.Type from friends f left join users u on f.FriendID = u.ID where f.UserID = ");
    strcat(sqlQuery,to_string(ID).c_str());
    rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, 0);//preparing the statement
    if (rc != SQLITE_OK) {

        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw "SqlException";
    }
    vector<FriendDTO> fr;
    while ((rc = sqlite3_step(stmt) == SQLITE_ROW)) //executing the statement
        fr.push_back(FriendDTO(stmt));
    return fr;
}

void Database::Unfriend(NewFriendDTO user) {
    char *sqlQuery = (char *)malloc((size_t) 300);
    strcpy(sqlQuery,"DELETE from friends where UserID = ");
    strcat(sqlQuery,to_string(user.UserID).c_str());
    strcat(sqlQuery," and FriendID = ");
    strcat(sqlQuery,to_string(user.FriendID).c_str());
    rc = sqlite3_exec(db, sqlQuery, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records deleted successfully\n");
    }
}

void Database::AddFriend(NewFriendDTO user) {
    char *sqlQuery = (char *)malloc((size_t) 300);
    strcpy(sqlQuery,"INSERT INTO friends VALUES (");
    strcat(sqlQuery,to_string(user.UserID).c_str());
    strcat(sqlQuery," , ");
    strcat(sqlQuery,to_string(user.FriendID).c_str());
    strcat(sqlQuery," , ");
    strcat(sqlQuery,to_string(user.Type).c_str());
    strcat(sqlQuery," ) ");
    rc = sqlite3_exec(db, sqlQuery, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
}

vector<FriendDTO> Database::GetNotFriends(int ID) {
    char *sqlQuery = (char *)malloc((size_t) 400);
    strcpy(sqlQuery,"SELECT ID as 'FriendID', FirstName, LastName from users where ID not in (SELECT FriendID from friends where UserID =  ");
    strcat(sqlQuery,to_string(ID).c_str());
    strcat(sqlQuery," ) and ID <>  ");
    strcat(sqlQuery,to_string(ID).c_str());
    rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, 0);//preparing the statement
    if (rc != SQLITE_OK) {

        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw "SqlException";
    }
    vector<FriendDTO> fr;
    while ((rc = sqlite3_step(stmt) == SQLITE_ROW)) //executing the statement
        fr.push_back(FriendDTO(stmt));
    return fr;
}

vector<ChatsDTO> Database::GetChats(int userID) {
    char *sqlQuery = (char *)malloc((size_t) 400);
    strcpy(sqlQuery,"SELECT ChatID, group_concat(FirstName || ' ' || LastName,', ') as  'Names' from chats left join users on UserID=ID where chatID IN(select chatID from chats c where c.userid= ");
    strcat(sqlQuery,to_string(userID).c_str());
    strcat(sqlQuery," ) and userID <> ");
    strcat(sqlQuery,to_string(userID).c_str());
    strcat(sqlQuery," group by chatID ");
    rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, 0);
    if (rc != SQLITE_OK) {

        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw "SqlException";
    }
    vector<ChatsDTO> chat;
    while ((rc = sqlite3_step(stmt) == SQLITE_ROW)) //executing the statement
        chat.push_back(ChatsDTO(stmt));
    return chat;
}

void Database::CreateNewChat(vector<int> users) {
    char *sqlQuery = (char *)malloc((size_t) 400);
    strcpy(sqlQuery,"SELECT max(chatID) from chats");
    rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, 0);
    if (rc != SQLITE_OK) {

        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw "SqlException";
    }
    int chatID;
    if ((rc = sqlite3_step(stmt) == SQLITE_ROW))
        chatID = sqlite3_column_int(stmt, 0) + 1;
    for(int userID : users)
    {
        char *insertQuery = (char *)malloc((size_t) 300);
        strcpy(insertQuery, "INSERT INTO chats VALUES (");
        strcat(insertQuery, to_string(chatID).c_str());
        strcat(insertQuery, " , ");
        strcat(insertQuery, to_string(userID).c_str());
        strcat(insertQuery, " ) ");
        rc = sqlite3_exec(db, insertQuery, NULL, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Records created successfully\n");
        }
    }
}

void Database::InsertMessage(MessageDTO message) {
    char *sqlQuery = (char *)malloc((size_t) 300);
    strcpy(sqlQuery,"INSERT INTO messages (chatID, UserID, Message, Date) VALUES (");
    strcat(sqlQuery,to_string(message.ChatID).c_str());
    strcat(sqlQuery," , ");
    strcat(sqlQuery,to_string(message.UserID).c_str());
    strcat(sqlQuery," , '");
    strcat(sqlQuery,message.Message);
    strcat(sqlQuery,"' , '");
    strcat(sqlQuery,message.Date);
    strcat(sqlQuery,"' ) ");
    rc = sqlite3_exec(db, sqlQuery, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
}

vector<MessageDTO> Database::GetMessage(int chatID) {
    char *sqlQuery = (char *)malloc((size_t) 400);
    strcpy(sqlQuery,"SELECT m.ChatID, m.UserID, FirstName, LastName, Message, Date from messages m left join users u on m.UserID = u.ID where m.ChatID = ");
    strcat(sqlQuery,to_string(chatID).c_str());
    strcat(sqlQuery, " order by Date desc ");
    rc = sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, 0);//preparing the statement
    if (rc != SQLITE_OK) {

        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        throw "SqlException";
    }
    vector<MessageDTO> message;
    while ((rc = sqlite3_step(stmt) == SQLITE_ROW)) //executing the statement
        message.push_back(MessageDTO(stmt));
    return message;
}
