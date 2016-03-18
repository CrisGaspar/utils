#include <unordered_set>
#include <stack>
#include <queue>
#include <memory>
#include <stdexcept>
#include <iostream>

using namespace std;

// arity of the tree
// Binary Search Tree
const int MAX_CHILD_NUM = 2;
const int LEFT = 0;
const int RIGHT = 1;

namespace efficient {

template <class T>
struct Node {
    Node<T>* children[MAX_CHILD_NUM];
    T elem;
    bool hasChildren;

    Node(const T& el) : elem(el), hasChildren(false) {
        for(auto child: children) {
            child = nullptr;
        }
    }

    Node() = delete;
    
};

template<class T>
void insert(Node<T>** rootPtr, const T& elem, int elemKey) {
    if (!rootPtr) {
        throw logic_error("BSTinsert: no address to store the root");
    }

    if (!(*rootPtr)) {
        *rootPtr = new Node<T>(elem);
        return;
    }

    Node<T>* root = *rootPtr;
    auto rootKey = (int)(root->elem);

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
template<class T>
Node<T>* createBST(const vector<T>& src) {
    bool first = true;
    Node<T>* root = nullptr;

    for (const auto &elem: src) {
        insert(&root, elem, (int) elem);
    }

    return root;
}

template<class T>
void clearTree(Node<T>* root) {
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

template<class T>
void clearTreeRecursive(Node<T>* root) {
    if (!root) return;

    for (auto child: root->children) {
        clearTreeRecursive(child);
    }
    delete root;
}

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

int main(int argc, char** argv) {
    vector<int> vals = { 5, 10, 2, 11, 4, 9, 12, 1, 2, 3};

    efficient::Node<int>* root = efficient::createBST(vals);

    auto coutf = [] (const int& i) { cout << i << " "; };
    unordered_set<efficient::Node<int>*> visited;

    cout << "Breadth first search: ";
    efficient::bfs(root, visited, coutf);
    cout << endl;

    visited.clear();
    cout << "Depth first search: ";
    efficient::dfs(root, visited, coutf);
    cout << endl;
    return 0; 
}
