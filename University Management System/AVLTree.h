#ifndef AVLTREE_H
#define AVLTREE_H

#include "University.h"
#include "utility.h"
#include <functional>
using namespace std;

class AVLNode {
public:
    University data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const University& uni);
};
class AVLTree {
private:
    void clear(AVLNode* node);
public:
    AVLNode* root;

    bool (*compare)(const University&, const University&);

    AVLTree() : root(nullptr), compare(compareByName) {}

    void clear();

    int getHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, const University& uni, bool (*compare)(const University&, const University&));

    // Define the SearchResult structure
    struct SearchResult {
        const University* university;
        SearchResult* next;

        SearchResult(const University* uni) : university(uni), next(nullptr) {}
    };

    SearchResult* searchInOrder(AVLNode* root, const string& name, function<bool(const University&, const string&)> searchCompare, SearchResult*& results);
    SearchResult* addToResultList(SearchResult* head, const University* university);
    void deleteResultList(SearchResult* head);
};

#endif // AVLTREE_H
