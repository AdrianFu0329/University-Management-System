#include "AVLTree.h"
#include "utility.h"
#include <algorithm>
#include <functional>
using namespace std;

AVLNode::AVLNode(const University& uni) : data(uni), left(nullptr), right(nullptr), height(1) {}

int AVLTree::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalanceFactor(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, const University& uni, bool (*compare)(const University&, const University&)) {
    if (node == nullptr) {
        return new AVLNode(uni);
    }

    if (compare(uni, node->data)) {
        node->left = insert(node->left, uni, compare);
    }
    else {
        node->right = insert(node->right, uni, compare);
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
        }
        return rightRotate(node);
    }

    if (balance < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
        }
        return leftRotate(node);
    }

    return node;
}

void AVLTree::clear() {
    clear(root);
    root = nullptr;
}

void AVLTree::clear(AVLNode* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// Update function declaration to include comparator
AVLTree::SearchResult* AVLTree::searchInOrder(AVLNode* root, const string& name, function<bool(const University&, const string&)> searchCompare, SearchResult*& results) {
    if (root == nullptr) {
        return nullptr;
    }

    if (searchCompare(root->data, name)) {
        results = addToResultList(results, &root->data);
    }

    searchInOrder(root->left, name, searchCompare, results);
    searchInOrder(root->right, name, searchCompare, results);

    return results;
}

AVLTree::SearchResult* AVLTree::addToResultList(SearchResult* head, const University* university) {
    SearchResult* newResult = new SearchResult(university);
    if (head == nullptr) {
        return newResult;
    }
    SearchResult* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = newResult;
    return head;
}

void AVLTree::deleteResultList(SearchResult* head) {
    while (head != nullptr) {
        SearchResult* temp = head;
        head = head->next;
        delete temp;
    }
}