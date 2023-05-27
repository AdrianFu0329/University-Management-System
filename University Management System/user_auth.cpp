#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <string>
#include <functional>
#include "user_auth.h"
#include "registered_user.h"
using namespace std;

string hash_password(const string& password) {
    hash<string> hasher;
    size_t hashed = hasher(password);
    return to_string(hashed);
}


UserNode* readUserData() {
    ifstream inputFile("users.txt");
    if (!inputFile) {
        cout << "Error opening file. Creating an empty list.\n";
        return nullptr;
    }

    UserNode* head = nullptr;
    UserNode* tail = nullptr;

    string username, password;
    while (inputFile >> username >> password) {
        UserNode* newNode = new UserNode;
        newNode->user.username = username;
        newNode->user.password = password;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    inputFile.close();
    return head;
}

void saveUserData(const UserNode* head) {
    ofstream outputFile("users.txt");
    if (!outputFile) {
        cout << "Error opening file. Unable to save user data.\n";
        return;
    }

    const UserNode* currentNode = head;
    while (currentNode != nullptr) {
        outputFile << currentNode->user.username << " " << currentNode->user.password << "\n";
        currentNode = currentNode->next;
    }

    outputFile.close();
}

void registerUser(AVLTree& tree, LinkedList& list, UserNode** head) {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;

    if (validateUser(username, "", *head)) {
        cout << "Username already exists. Please choose a different username.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    UserNode* newNode = new UserNode;
    newNode->user.username = username;
    newNode->user.password = hash_password(password);  // Hash password here
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (*head == nullptr) {
        *head = newNode;
    }
    else {
        UserNode* currentNode = *head;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
        newNode->prev = currentNode;
    }

    saveUserData(*head); // pass data through node
    cout << "User registered successfully.\n";
    displayRegisteredUserOptions(tree, list, head);
}

bool validateUser(const string& username, const string& password, const UserNode* head) {
    const UserNode* currentNode = head;
    while (currentNode != nullptr) {
        // Compare hash of input password to stored hash
        if (currentNode->user.username == username && currentNode->user.password == password) {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

bool login(const UserNode* head) {
    string username, password;
    cout << "\nEnter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // Hash the password before validation
    string hashed_password = hash_password(password);

    if (validateUser(username, hashed_password, head)) {
        cout << "\nLogin successful. Welcome, " << username << "!\n";
    }
    else {
        cout << "\nInvalid username or password. Please try again.\n";
        return false;
    }
    return true;
}


void logout() {
    cout << "Logged out successfully! \n";
}