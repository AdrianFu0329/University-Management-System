#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <random>
#include <functional>
#include "University.h"
using namespace std;

class Node {
public:
    University data;
    Node* next;

    Node(const University& uni) : data(uni), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    struct SearchResult {
        const University* university;
        SearchResult* next;

        SearchResult(const University* uni) : university(uni), next(nullptr) {}
    };

    void push(const University& uni);
    int size();
    University& operator[](int index);
    Node* split(Node* head);
    Node* merge(Node* first, Node* second, bool (*compFunc)(const University&, const University&));
    void mergeSort(Node** headRef, bool (*compFunc)(const University&, const University&));
    void print();
    void search(const string& uniName, function<bool(const University&, const string&)> searchCompare, SearchResult*& results);
    SearchResult* addToResultList(SearchResult* head, const University* university);


};

void shuffleLinkedList(LinkedList& list);

#endif // LINKEDLIST_H
