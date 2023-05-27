#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <string>
#include <fstream>
#include "AVLTree.h"
#include "LinkedList.h"
using namespace std;

struct User {
    string username;
    string password;
};

struct UserNode {
    User user;
    UserNode* next;
    UserNode* prev;
};

// Function prototypes
UserNode* readUserData();
void saveUserData(const UserNode* head);
bool validateUser(const string& username, const string& password, const UserNode* head);
void registerUser(AVLTree& tree, LinkedList& list, UserNode** userList);
bool login(const UserNode* head);
void logout();
#endif /* USER_AUTH_H */