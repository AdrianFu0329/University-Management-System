#ifndef UTILITY_H
#define UTILITY_H

#include "AVLTree.h"
#include "LinkedList.h"
using namespace std;

class AVLTree;  // Forward declaration of AVLTree
struct AVLNode; // Forward declaration of AVLNode

void printInOrder(AVLNode* node, bool (*compare)(const University&, const University&));
void printLine(char ch);
void printHeader();
void printFooter(const string& moduleName);
void readUniversityData(const string& filename, AVLTree& tree);
void readUniversityDataToLinkedList(const string& filename, LinkedList& list, bool (*compFunc)(const University&, const University&));
bool compareByName(const University& u1, const University& u2);
bool compareByLocation(const University& u1, const University& u2);
bool compareByRank(const University& u1, const University& u2);
bool compareByAcademicReputation(const University& u1, const University& u2);
bool compareByFacultyStudentRatio(const University& u1, const University& u2);
bool compareByEmployerReputation(const University& u1, const University& u2);
bool searchCompareByName(const University& uni, const string& name);
bool searchCompareByLocation(const University& uni, const string& location);
bool searchCompareByRank(const University& uni, const string& rankStr);
bool searchCompareByAcademicReputation(const University& uni, const string& arStr);
bool searchCompareByFacultyStudentRatio(const University& uni, const string& fsrStr);
bool searchCompareByEmployerReputation(const University& uni, const string& erStr);
void sortUniversityInformation(AVLTree& tree, LinkedList& list, const string role);
void searchIndividualUniversityDetails(AVLTree& tree, LinkedList& list, const string role);
#endif /* UTILITY_H */