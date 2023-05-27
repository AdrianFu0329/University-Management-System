#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
#include "AVLTree.h"
#include "normal_user.h"
#include "registered_user.h"
#include "mohe_admin.h"
#include "utility.h"
#include "user_auth.h"
#include "constants.h"

using namespace std;

const int WIDTH = 80;

void displayMenuOptions() {
    int totalPadding = WIDTH - 2; // For the asterisks at the start and end of each line

    string options[] = {
        "",
        "Welcome to the University Recommendation System.",
        "You would like to login as a:",
        "1. Normal User",
        "2. Registered User (Customer)",
        "3. MoHE Admin",
        "4. Exit",
        ""
    };

    for (const string& option : options) {
        int totalTextWidth = totalPadding - option.length();
        int leftPadding = totalTextWidth / 2;
        int rightPadding = totalTextWidth - leftPadding;

        cout << "*" << setw(leftPadding) << "" << option << setw(rightPadding) << "" << "*\n";
    }
}

int getUserChoice() {
    int choice;
    // ANSI code for red color
    cout << "\n\033[1;33mEnter your choice: \033[0m";
    if (!(cin >> choice) || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid choice (1-4).\n\n";
        return 0;
    }
    return choice;
}

int main() {
    int choice;
    int count = 0;

    // Create an AVLTree object and read university data into it
    AVLTree tree;
    LinkedList list;
    UserNode* userList = nullptr;

    tree.compare = compareByName;

    // Update your readUniversityData function to fill the LinkedList as well
    readUniversityData("input.csv", tree);
    readUniversityDataToLinkedList("input.csv", list, tree.compare);

    while (true) {
        printHeader();
        displayMenuOptions();
        printFooter("Main Menu");

        int choice = getUserChoice();

        if (choice == 0) {
            continue;
        }

        if (choice == 4) {
            break;
        }

        switch (choice) {
        case 1:
            displayNormalUserOptions(tree, list, &userList);
            break;
        case 2:
            displayRegisteredUserOptions(tree, list, &userList);
            break;
        case 3:
            displayMoHEAdminOptions(tree);
            break;
        }
        count = 0; // Reset the count
        printFooter("Main Menu");
    }
}
