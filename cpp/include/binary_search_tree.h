#include <unordered_set>
#include <stack>
#include <queue>
#include <memory>
#include <stdexcept>
#include <iostream>

using namespace std;

// Binary Search Tree
const int MAX_CHILD_NUM = 2;
const int LEFT = 0;
const int RIGHT = 1;

namespace efficient {

template <class T>
struct Node {
    Node<T>* children[MAX_CHILD_NUM];

    // NOTE: T must implement the conversion-to-key operator:
    // operator Key() const {
    //  // return a hash or some unique_id that will serve as key for search operations };
    //
    // Usually Key = size_t or Key = string
    // but could be any type that defines a strict ordering and
    // operators <,>,== are implemented for the Key type
    T elem;

    Node(const T& el) : elem(el) {
        for(auto &child: children) {
            child = nullptr;
        }
    }

    Node() = delete;
};


// TODO: implement delete-T and rebalancing !!!

template<class T, class Key>
Node<T>* find(Node<T>* root, const Key& elemKey) {
    if (!root)
        return nullptr;

    auto rootKey = (const Key&)(root->elem);
    if (rootKey == elemKey)
        return root;

    if ( elemKey > rootKey)
        return find(root->children[RIGHT], elemKey);

    return find(root->children[LEFT], elemKey);
}

// Key for the element gets passed explictly to avoid calling the conversion operator
// on every recursive call
template<class T, class Key>
void insert(Node<T>** rootPtr, const T& elem, const Key& elemKey) {
    if (!rootPtr) {
        throw logic_error("BSTinsert: no address to store the root");
    }

    if (!(*rootPtr)) {
        *rootPtr = new Node<T>(elem);
        return;
    }

    Node<T>* root = *rootPtr;
    auto rootKey = (const Key&)(root->elem);

    if (elemKey == rootKey) {
        // in tree already
        return;
    }

    if (elemKey > rootKey) {
        if (!root->children[RIGHT]) {
            root->children[RIGHT] = new Node<T>(elem);
            return;
        }
        return insert(&root->children[RIGHT], elem, elemKey);
    }

    // Must be Left side
    if (!root->children[LEFT]) {
        root->children[LEFT] = new Node<T>(elem);
        return;
    }
    return insert(&root->children[LEFT], elem, elemKey);
}

// Binary Search Tree
template<class T, class Key>
Node<T>* createBST(const vector<T>& src) {
    bool first = true;
    Node<T>* root = nullptr;

    for (const auto &elem: src) {
        insert(&root, elem, (const Key&) elem);
    }
    return root;
}


template<class T>
void clearBST(Node<T>* root) {
    if (!root) return;

    for (auto child: root->children) {
        clearBST(child);
    }
    delete root;
}

template<class T>
void clearBSTNonRecursive(Node<T>* root) {
    if (!root) return;

    stack<Node<T>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<T>* node = s.top();
        if (!node->hasChildren) {
            // leaf. can deallocate
            s.pop();
            delete node;
        }
        else {
            for (auto child: node->children) {
                if (child) {
                    s.push(child);
                }
            }
        }
    }
}

// Depth-first-search that applies function f to each element
template <class T, class Func>
void dfs(Node<T>* root, unordered_set<Node<T>*> &visited, const Func& f) {
    if (!root)
        return;

    visited.insert(root);
    f(root->elem);

    for (auto child: root->children) {
        if (child && visited.find(child) == visited.end()) {
            dfs(child, visited, f);
        }
    }
}

// Breadth-first-search that applies function f to each element
template <class T, class Func>
void bfs(Node<T>* root, unordered_set<Node<T>*> &visited, const Func& f) {
    if (!root)
        return;

    queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* cur = q.front();
        q.pop();

        if (visited.find(cur) == visited.end()) {
            visited.insert(cur);
            f(cur->elem);

            for (auto child: cur->children) {
                if (child && visited.find(child) == visited.end()) {
                    q.push(child);
                }
            }
        }
    }
}

} // namespace
