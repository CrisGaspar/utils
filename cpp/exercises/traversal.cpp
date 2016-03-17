using namespace std;

// arity of the tree
const int MAX_CHILD_NUM = 10;

template <class T>
class Node {
    Node* children[MAX_CHILD_NUM];
    T elem;

    Node() {
        for(auto child: children) {
            child = nullptr;
        }
    }

    N
}

void dfs(Node* root) {
    if (!root)
        return;
    
    cout << root->elem << " ";
    for (auto child: root->children) {
        dfs(child);
    }
}

void bfs(Node* root) {
    if (!root)
        return;
    
    if (!root->parent) {
        // root of the whole tree
        cout << root->elem << " ";
    }

    for (auto child: root->children) {
        cout << child->elem << " ";
    }

    for (auto child: root->children) {
        cout << child->elem << " ";
        bfs(child);
}
