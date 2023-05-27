#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "AVLTree.h"
#include "LinkedList.h"
#include "constants.h"
using namespace std;

template <typename T>
struct identity {
    using type = T;
};

template <typename T>
T safeStringToNumber(const string& str, identity<T>) {
    if (str.empty() || str == "-") {
        return T(0);
    }
    return stod(str);
}

int safeStringToNumber(const string& str, identity<int>) {
    if (str.empty() || str == "-") {
        return 0;
    }
    if (str.back() == '+') {
        return stoi(str.substr(0, str.size() - 1));
    }
    return stoi(str);
}

template <typename T>
T safeStringToNumber(const string& str) {
    return safeStringToNumber(str, identity<T>());
}

string readField(stringstream& ss) {
    string field;
    char ch;

    bool in_quotes = false;
    while (ss.get(ch)) {
        if (ch == '"') {
            in_quotes = !in_quotes;
        }
        else if (ch == ',' && !in_quotes) {
            break;
        }
        else {
            field.push_back(ch);
        }
    }

    return field;
}

void shuffleLinkedList(LinkedList& list) {
    random_device rd;
    mt19937 g(rd());

    int n = list.size();
    for (int i = n - 1; i > 0; i--) {
        uniform_int_distribution<> distr(0, i);
        int j = distr(g);
        swap(list[i], list[j]);
    }
}

void printLine(char ch) {
    for (int i = 0; i < WIDTH; ++i) cout << ch;
    cout << '\n';
}

void printHeader() {
    string title = "University Recommendation System - MoHE";
    int totalPadding = WIDTH - 2;
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;

    int totalHeaderPadding = WIDTH - title.length() - 2;
    int leftHeaderPadding = totalHeaderPadding / 2;
    int rightHeaderPadding = totalHeaderPadding - leftHeaderPadding;

    printLine('*');
    cout << "*" << setw(leftPadding) << "" << setw(rightPadding) << "" << "*\n";
    cout << "*" << setw(leftHeaderPadding) << "" << title << setw(rightHeaderPadding) << "" << "*\n";
    cout << "*" << setw(leftPadding) << "" << setw(rightPadding) << "" << "*\n";
    printLine('*');
}

void printFooter(const string& moduleName) {
    string title = moduleName;
    int totalPadding = WIDTH - 2;
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;

    int totalHeaderPadding = WIDTH - title.length() - 2;
    int leftHeaderPadding = totalHeaderPadding / 2;
    int rightHeaderPadding = totalHeaderPadding - leftHeaderPadding;

    printLine('*');
    cout << "*" << setw(leftPadding) << "" << setw(rightPadding) << "" << "*\n";
    cout << "*" << setw(leftHeaderPadding) << "" << title << setw(rightHeaderPadding) << "" << "*\n";
    cout << "*" << setw(leftPadding) << "" << setw(rightPadding) << "" << "*\n";
    printLine('*');
}


void readUniversityData(const string& filename, AVLTree& tree) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Unable to open the file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);  // Skip the header line

    LinkedList universities;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        University uni;

        try {
            // Rank
            token = readField(ss);
            uni.rank = safeStringToNumber<int>(token);

            // Institution
            token = readField(ss);
            uni.name = token;

            // Skip LocationCode
            token = readField(ss);

            // Location
            token = readField(ss);
            uni.location = token;

            // Read the remaining fields
            token = readField(ss);
            uni.ar = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.arRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.er = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.erRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.fsr = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.fsrRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.cpf = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.cpfRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.ifr = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.ifrRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.isr = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.isrRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.irn = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.irnRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.ger = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.gerRank = safeStringToNumber<int>(token);

        }
        catch (const invalid_argument& e) {
            cerr << "Error reading data for university: " << uni.name << ". Field causing the issue: " << token << ". Skipping this entry." << endl;
            continue;
        }

        universities.push(uni);
    }

    file.close();

    // Randomly shuffle the universities
    shuffleLinkedList(universities);

    // Now insert the universities into the tree
    Node* current = universities.head;
    while (current != nullptr) {
        tree.root = tree.insert(tree.root, current->data, tree.compare);
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

void printInOrder(AVLNode* node, bool (*compare)(const University&, const University&)) {
    if (node == nullptr) {
        return;
    }

    printInOrder(node->left, compare);
    cout << "University Name: " << node->data.name << ", "
        << "Location: " << node->data.location << ", "
        << "Rank: " << node->data.rank << endl;
    printInOrder(node->right, compare);
}

void readUniversityDataToLinkedList(const string& filename, LinkedList& list, bool (*compFunc)(const University&, const University&)) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Unable to open the file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);  // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        University uni;

        try {
            // Rank
            token = readField(ss);
            uni.rank = safeStringToNumber<int>(token);

            // Institution
            token = readField(ss);
            uni.name = token;

            // Skip LocationCode
            token = readField(ss);

            // Location
            token = readField(ss);
            uni.location = token;

            // Read the remaining fields
            token = readField(ss);
            uni.ar = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.arRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.er = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.erRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.fsr = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.fsrRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.cpf = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.cpfRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.ifr = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.ifrRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.isr = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.isrRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.irn = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.irnRank = safeStringToNumber<int>(token);
            token = readField(ss);
            uni.ger = safeStringToNumber<double>(token);
            token = readField(ss);
            uni.gerRank = safeStringToNumber<int>(token);

        }
        catch (const invalid_argument& e) {
            cerr << "Error reading data for university: " << uni.name << ". Field causing the issue: " << token << ". Skipping this entry." << endl;
            continue;
        }

        list.push(uni);
    }

    file.close();

    // Now sort the linked list
    list.mergeSort(&list.head, compFunc);
}

bool compareByName(const University& u1, const University& u2) {
    return u1.name < u2.name;
}

bool compareByLocation(const University& u1, const University& u2) {
    return u1.location < u2.location;
}

bool compareByRank(const University& u1, const University& u2) {
    return u1.rank < u2.rank;
}

bool compareByAcademicReputation(const University& u1, const University& u2) {
    return u1.ar > u2.ar;
}

bool compareByFacultyStudentRatio(const University& u1, const University& u2) {
    return u1.fsr > u2.fsr;
}

bool compareByEmployerReputation(const University& u1, const University& u2) {
    return u1.er > u2.er;
}

bool searchCompareByName(const University& uni, const string& name) {
    return uni.name.substr(0, name.size()) == name;
}

bool searchCompareByLocation(const University& uni, const string& location) {
    return uni.location.substr(0, location.size()) == location;
}

bool searchCompareByRank(const University& uni, const string& rankStr) {
    int rank = stoi(rankStr);  // convert string to integer
    return uni.rank == rank;
}

bool searchCompareByAcademicReputation(const University& uni, const string& arStr) {
    double ar = stod(arStr); // convert string to double
    return uni.ar == ar;
}

bool searchCompareByFacultyStudentRatio(const University& uni, const string& fsrStr) {
    double fsr = stod(fsrStr); // convert string to double
    return uni.fsr == fsr;
}

bool searchCompareByEmployerReputation(const University& uni, const string& erStr) {
    double er = stod(erStr); // convert string to double
    return uni.er == er;
}

void sortUniversityInformation(AVLTree& tree, LinkedList& list, string role) {
    int sortAlgorithm;
    if (role == "normal") {
        cout << "\nSelect sorting algorithm:\n";
        cout << "1. Merge Sort\n";
        cout << "2. In-Order Traversal of AVL Tree\n\n";
        cout << "Enter your choice: ";
        cin >> sortAlgorithm;
    }
    else {
        sortAlgorithm = 1;
    }

    int sortOption;
    cout << "\nSelect sorting option:\n";
    cout << "1. Name\n";
    cout << "2. Location\n";
    cout << "3. Rank\n";
    cout << "4. Academic Reputation\n";
    cout << "5. Faculty Student Ratio\n";
    cout << "6. Employer Reputation\n\n";
    cout << "Enter your choice: ";
    cin >> sortOption;

    switch (sortOption) {
    case 1:
        tree.compare = compareByName;
        break;
    case 2:
        tree.compare = compareByLocation;
        break;
    case 3:
        tree.compare = compareByRank;
        break;
    case 4:
        tree.compare = compareByAcademicReputation;
        break;
    case 5:
        tree.compare = compareByFacultyStudentRatio;
        break;
    case 6:
        tree.compare = compareByEmployerReputation;
        break;
    default:
        cout << "Invalid option. No sorting will be applied.\n";
        return;
    }

    if (sortAlgorithm == 1) {
        // Merge Sort
        readUniversityDataToLinkedList("input.csv", list, tree.compare);
        auto start = chrono::high_resolution_clock::now();
        list.mergeSort(&list.head, tree.compare);
        auto end = chrono::high_resolution_clock::now();
        list.print();
        chrono::duration<double> elapsed = end - start;
        if (role == "normal") {
            cout << "Merge Sort Time Elapsed: " << elapsed.count() << "s\n";
        }

    }
    else if (sortAlgorithm == 2) {
        // AVL Tree In-Order Traversal
        tree.clear();
        auto start = chrono::high_resolution_clock::now();
        readUniversityData("input.csv", tree);
        auto end = chrono::high_resolution_clock::now();
        printInOrder(tree.root, tree.compare);
        chrono::duration<double> elapsed = end - start;
        if (role == "normal") {
            cout << "AVL Tree Sort Time Elapsed: " << elapsed.count() << "s\n";
        }

    }
    else {
        cout << "Invalid algorithm. No sorting will be applied.\n";
    }
}

void searchIndividualUniversityDetails(AVLTree& tree, LinkedList& list, string role) {
    string searchValue;
    string searchField;

    int choice;
    if (role == "normal") {
        cout << "\nChoose search method:\n";
        cout << "1. Depth-First Search (DFS) Traversal \n";
        cout << "2. Linear Search\n\n";
        cout << "Enter your choice: ";
        cin >> choice;
    }
    else {
        choice = 2;
    }




    cout << "\nChoose search field:\n";
    cout << "1. Name\n";
    cout << "2. Location\n";
    cout << "3. Rank\n";
    cout << "4. Academic Reputation\n";
    cout << "5. Faculty Student Ratio\n";
    cout << "6. Employer Reputation\n\n";
    cout << "Enter your choice: ";

    int searchChoice;
    cin >> searchChoice;

    function<bool(const University&, const string&)> searchCompare;

    switch (searchChoice) {
    case 1:
        searchCompare = searchCompareByName;
        searchField = "Name";
        break;
    case 2:
        searchCompare = searchCompareByLocation;
        searchField = "Location";
        break;
    case 3:
        searchCompare = searchCompareByRank;
        searchField = "Rank";
        break;
    case 4:
        searchCompare = searchCompareByAcademicReputation;
        searchField = "Academic Reputation";
        break;
    case 5:
        searchCompare = searchCompareByFacultyStudentRatio;
        searchField = "Faculty/Student Ratio";
        break;
    case 6:
        searchCompare = searchCompareByEmployerReputation;
        searchField = "Employer Reputation";
    default:
        cout << "Invalid option. No search will be applied.\n";
        return;
    }

    cout << "\n\nEnter the " << searchField << ": ";
    cin.ignore();
    getline(cin, searchValue);

    AVLTree::SearchResult* avlTreeSearchResults = nullptr;
    LinkedList::SearchResult* linkedListSearchResults = nullptr;

    switch (choice) {
    case 1: {
        // search in AVL Tree
        auto start = chrono::high_resolution_clock::now();
        tree.searchInOrder(tree.root, searchValue, searchCompare, avlTreeSearchResults);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        if (avlTreeSearchResults != nullptr) {
            cout << "\nUniversities found:\n";
            AVLTree::SearchResult* currAVL = avlTreeSearchResults;
            while (currAVL != nullptr) {
                cout << "University name: " << currAVL->university->name << "\n";
                cout << "Location: " << currAVL->university->location << "\n";
                cout << "Rank: " << currAVL->university->rank << "\n\n";
                AVLTree::SearchResult* temp = currAVL;
                currAVL = currAVL->next;
                delete temp;
            }
            if (role == "normal") {
                cout << "AVL Tree Search Time Elapsed: " << elapsed.count() << "s\n";
            }
        }
        else {
            cout << "No universities found.\n";
        }

        break;
    }
    case 2: {
        // search in Linked List
        auto start = chrono::high_resolution_clock::now();
        list.search(searchValue, searchCompare, linkedListSearchResults);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        if (linkedListSearchResults != nullptr) {
            cout << "\nUniversities found:\n";
            LinkedList::SearchResult* currLL = linkedListSearchResults;
            while (currLL != nullptr) {
                cout << "University name: " << currLL->university->name << "\n";
                cout << "Location: " << currLL->university->location << "\n";
                cout << "Rank: " << currLL->university->rank << "\n\n";
                LinkedList::SearchResult* temp = currLL;
                currLL = currLL->next;
                delete temp;
            }
            if (role == "normal") {
                cout << "Link Search Time Elapsed: " << elapsed.count() << "s\n";
            }
        }
        else {
            cout << "No universities found.\n";
        }

        break;
    }
    default:
        cout << "Invalid choice.\n";
        return;
    }
}