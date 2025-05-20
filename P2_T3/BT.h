#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <queue>
#include <vector>

using namespace std;

template <class E>
struct node {
    E item;
    node<E>* left;
    node<E>* right;
    node() {
        left = right = nullptr;
    }
    node(E it, node<E>* l = NULL, node<E>* r = NULL) {
        item = it;
        left = l;
        right = r;
    }
};

template <class E>
class binary_tree {
protected:
    node<E>* root;

    bool TreeEqual(node<E>*, node<E>*);
    node<E>* copyTree(node<E>* treeRoot) const;
    void destroyTree(node<E>* treeRoot);
    int treeHeight(node<E>* rt);
    int size(node<E>* rt);

    void preorder(node<E>* treeRoot, ostream&, string) const;
    void inorder(node<E>* treeRoot, ostream&, string) const;
    void postorder(node<E>* treeRoot, ostream&, string) const;
    bool balancedHelper(node<E>*);
    vector<E> toVectorLevel(node<E>*);
    void IP1(node<E>* rt, int);

public:
    binary_tree();
    binary_tree(const binary_tree<E>& bt);
    ~binary_tree();

    binary_tree<E>& operator=(const binary_tree<E>& bt);
    bool operator==(binary_tree<E>);

    bool isEmpty() const;
    int treeHeight() { return treeHeight(root); }
    int size() { return size(root); }

    void preorder(ostream&, string) const;
    void inorder(ostream&, string) const;
    void postorder(ostream&, string) const;
    bool balanced() { return balancedHelper(root); }
    vector<E> toVectorLevel() { return toVectorLevel(root); }
    void IP() { IP1(root, 0); }
};

// Constructor
template <class E>
binary_tree<E>::binary_tree() {
    root = nullptr;
}

// Copy Constructor
template <class E>
binary_tree<E>::binary_tree(const binary_tree<E>& bt) {
    root = copyTree(bt.root);
}

// Destructor
template <class E>
binary_tree<E>::~binary_tree() {
    destroyTree(root);
    root = nullptr;
}

// Assignment Operator
template <class E>
binary_tree<E>& binary_tree<E>::operator=(const binary_tree<E>& bt) {
    if (this != &bt) {
        destroyTree(root);
        root = copyTree(bt.root);
    }
    return *this;
}

// Equality Operator
template <class E>
bool binary_tree<E>::operator==(binary_tree<E> tree2) {
    return TreeEqual(root, tree2.root);
}

// TreeEqual Function
template <class E>
bool binary_tree<E>::TreeEqual(node<E>* root1, node<E>* root2) {
    if (root1 == nullptr && root2 == nullptr)
        return true;
    else if (root1 == nullptr || root2 == nullptr)
        return false;
    else if (root1->item == root2->item)
        return TreeEqual(root1->left, root2->left) &&
               TreeEqual(root1->right, root2->right);
    else
        return false;
}

// CopyTree Function
template <class E>
node<E>* binary_tree<E>::copyTree(node<E>* subRoot) const {
    if (subRoot == nullptr)
        return nullptr;
    return new node<E>(subRoot->item, copyTree(subRoot->left), copyTree(subRoot->right));
}

// DestroyTree Function
template <class E>
void binary_tree<E>::destroyTree(node<E>* treeRoot) {
    if (treeRoot != nullptr) {
        destroyTree(treeRoot->left);
        destroyTree(treeRoot->right);
        delete treeRoot;
    }
}

// TreeHeight Function
template <class E>
int binary_tree<E>::treeHeight(node<E>* rt) {
    if (rt == nullptr)
        return 0;
    int leftHeight = treeHeight(rt->left);
    int rightHeight = treeHeight(rt->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Size Function
template <class E>
int binary_tree<E>::size(node<E>* rt) {
    if (rt == nullptr)
        return 0;
    return size(rt->left) + size(rt->right) + 1;
}

// Preorder Traversal (Public)
template <class E>
void binary_tree<E>::preorder(ostream& os, string S) const {
    preorder(root, os, S);
}

// Preorder Traversal (Internal)
template <class E>
void binary_tree<E>::preorder(node<E>* treeRoot, ostream& os, string S) const {
    if (treeRoot != nullptr) {
        os << treeRoot->item << S;
        preorder(treeRoot->left, os, S);
        preorder(treeRoot->right, os, S);
    }
}

// Inorder Traversal (Public)
template <class E>
void binary_tree<E>::inorder(ostream& os, string S) const {
    inorder(root, os, S);
}

// Inorder Traversal (Internal)
template <class E>
void binary_tree<E>::inorder(node<E>* treeRoot, ostream& os, string S) const {
    if (treeRoot != nullptr) {
        inorder(treeRoot->left, os, S);
        os << treeRoot->item << S;
        inorder(treeRoot->right, os, S);
    }
}

// Postorder Traversal (Public)
template <class E>
void binary_tree<E>::postorder(ostream& os, string S) const {
    postorder(root, os, S);
}

// Postorder Traversal (Internal)
template <class E>
void binary_tree<E>::postorder(node<E>* treeRoot, ostream& os, string S) const {
    if (treeRoot != nullptr) {
        postorder(treeRoot->left, os, S);
        postorder(treeRoot->right, os, S);
        os << treeRoot->item << S;
    }
}

// Balanced Helper Function
template <class E>
bool binary_tree<E>::balancedHelper(node<E>* subRoot) {
    if (subRoot == nullptr)
        return true;
    int leftHeight = treeHeight(subRoot->left);
    int rightHeight = treeHeight(subRoot->right);
    return abs(leftHeight - rightHeight) <= 1 &&
           balancedHelper(subRoot->left) &&
           balancedHelper(subRoot->right);
}

// ToVectorLevel Function
template <class E>
vector<E> binary_tree<E>::toVectorLevel(node<E>* subRoot) {
    vector<E> result;
    if (subRoot == nullptr)
        return result;
    queue<node<E>*> q;
    q.push(subRoot);
    while (!q.empty()) {
        node<E>* current = q.front();
        q.pop();
        result.push_back(current->item);
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
    return result;
}

// Indentation Print Function
template <class E>
void binary_tree<E>::IP1(node<E>* rt, int Indent) {
    if (rt != nullptr) {
        for (int k = 0; k < Indent; k++)
            cout << " ";
        cout << rt->item << endl;
        IP1(rt->left, Indent + 3);
        IP1(rt->right, Indent + 3);
    }
}

#endif