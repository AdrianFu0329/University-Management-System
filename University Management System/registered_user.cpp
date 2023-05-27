#include <iostream>
#include <limits>
#include "registered_user.h"
#include "AVLTree.h"
#include "LinkedList.h"
#include "utility.h"
#include "user_auth.h"
using namespace std;

void displayRegisteredUserOptions(AVLTree& tree, LinkedList& list, UserNode** userList) {
    *userList = readUserData();

    int choice;
    bool isLoggedIn = false;

    while (true) {
        if (!isLoggedIn) {
            cout << "\nRegistered User Options:\n";
            cout << "1. Login\n";
            cout << "2. Return to main menu\n\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice) || choice < 1 || choice > 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid choice (1-2).\n\n";
                continue;
            }

            switch (choice) {
            case 1:
                if (login(*userList)) {
                    isLoggedIn = true;
                }
                break;
            case 2:
                return;  // return to main menu
            default:
                cout << "Invalid choice. Please try again.\n\n";
                break;
            }
        }
        else {
            cout << "\nRegistered User Options:\n";
            cout << "1. Logout\n";
            cout << "2. Sort university information\n";
            cout << "3. Search universities details based on customer decision\n";
            cout << "4. Save favorite universities\n";
            cout << "5. Send feedback to MoHE\n";
            cout << "6. Read feedback reply\n";
            cout << "7. Return to main menu\n\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice) || choice < 1 || choice > 7) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid choice (1-7).\n\n";
                continue;
            }

            switch (choice) {
            case 1:
                logout();
                isLoggedIn = false;
                break;
            case 2:
                sortUniversityInformation(tree, list, "registed");
                break;
            case 3:
                searchIndividualUniversityDetails(tree, list, "registed");
                break;
            case 4:
                // call the function to save favorite universities here
                break;
            case 5:
                // call the function to send feedback to MoHE here
                break;
            case 6:
                // call the function to read feedback reply here
                break;
            case 7:
                logout();
                isLoggedIn = false;
                return;  // return to main menu
            default:
                cout << "Invalid choice. Please try again.\n\n";
                break;
            }
        }
    }
}