#include <iostream>
#include "mohe_admin.h"
#include "AVLTree.h"
#include "utility.h"
using namespace std;

void displayMoHEAdminOptions(AVLTree& tree) {
    int choice;
    int count = 0;

    while (true) {
        cout << "\nMoHE Admin Options:\n";
        cout << ++count << ". Login and logout\n";
        cout << ++count << ". Display all registered users' details\n";
        cout << ++count << ". Modify a user detail\n";
        cout << ++count << ". Delete user accounts based on inactivity status\n";
        cout << ++count << ". Move back and forth between the feedback of registered users\n";
        cout << ++count << ". Reply to the registered user's feedback\n";
        cout << ++count << ". Generate a report of top 10 universities\n";
        cout << ++count << ". Return to main menu\n\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";

        if (!(cin >> choice) || choice < 1 || choice > count) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice (1-4).\n\n";
            continue;
        }

        if (choice == 8) {
            break;
        }
    }
}
