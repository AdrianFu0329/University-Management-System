#include <iostream>
#include <iomanip>
#include "normal_user.h"
#include "AVLTree.h"
#include "LinkedList.h"
#include "utility.h"
#include "constants.h"
using namespace std;

void displayNormalUserMenuOptions() {
    int totalPadding = WIDTH - 2; // For the asterisks at the start and end of each line
    int count = 0;

    string options[] = {
        "",
        "Normal User Options:",
        "1. Display all universities",
        "2. Sort university information",
        "3. Search individual university details",
        "4. Register as user",
        "5. Return to main menu",
        ""
    };

    for (const string& option : options) {
        int totalTextWidth = totalPadding - option.length();
        int leftPadding = totalTextWidth / 2;
        int rightPadding = totalTextWidth - leftPadding;

        cout << "*" << setw(leftPadding) << "" << option << setw(rightPadding) << "" << "*\n";
    }
}

int getNormalUserChoice() {
    int choice;
    // ANSI code for red color
    cout << "\n\033[1;33mEnter your choice: \033[0m";
    if (!(cin >> choice) || choice < 1 || choice > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid choice (1-4).\n\n";
        return 0;
    }
    return choice;
}

void displayNormalUserOptions(AVLTree& tree, LinkedList& list, UserNode** userList) { // Added userList parameter
    int choice;
    int count = 0;

    while (true) {
        printHeader();
        displayNormalUserMenuOptions();
        printFooter("Normal User");

        int choice = getNormalUserChoice();

        if (choice == 5) {
            break;
        }

        switch (choice) {
        case 1:
            printInOrder(tree.root, tree.compare);
            break;
        case 2:
            sortUniversityInformation(tree, list, "normal");
            break;
        case 3:
            searchIndividualUniversityDetails(tree, list, "normal");
            break;
        case 4:
            registerUser(tree, list, userList); // Use registerUser function from user_auth.cpp
            break;
        }
        count = 0; // Reset the count
    }
}