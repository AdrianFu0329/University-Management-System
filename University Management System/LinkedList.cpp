#include "LinkedList.h"
#include <iostream>
#include <functional>
using namespace std;

void LinkedList::push(const University& uni) {
    Node* newNode = new Node(uni);
    newNode->next = head;
    head = newNode;
}

int LinkedList::size() {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

University& LinkedList::operator[](int index) {
    Node* current = head;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->next;
    }
    return current->data;
}

Node* LinkedList::split(Node* head) {
    Node* slow = head;
    Node* fast = head->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    Node* temp = slow->next;
    slow->next = nullptr;
    return temp;
}

Node* LinkedList::merge(Node* first, Node* second, bool (*compFunc)(const University&, const University&)) {
    if (first == nullptr) {
        return second;
    }
    else if (second == nullptr) {
        return first;
    }

    Node* result = nullptr;

    if (compFunc(first->data, second->data)) {
        result = first;
        result->next = merge(first->next, second, compFunc);
    }
    else {
        result = second;
        result->next = merge(first, second->next, compFunc);
    }

    return result;
}

void LinkedList::mergeSort(Node** headRef, bool (*compFunc)(const University&, const University&)) {
    Node* head = *headRef;
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* second = split(head);

    mergeSort(&head, compFunc);
    mergeSort(&second, compFunc);

    *headRef = merge(head, second, compFunc);
}

void LinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << "Name: " << current->data.name << ", Location: " << current->data.location << ", Rank: " << current->data.rank << endl;
        current = current->next;
    }
}

void LinkedList::search(const string& uniName, function<bool(const University&, const string&)> searchCompare, SearchResult*& results) {
    Node* current = head;
    while (current != nullptr) {
        if (searchCompare(current->data, uniName)) {
            results = addToResultList(results, &current->data);
        }
        current = current->next;
    }
}

LinkedList::SearchResult* LinkedList::addToResultList(SearchResult* head, const University* university) {
    SearchResult* newNode = new SearchResult(university);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        SearchResult* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    return head;
}