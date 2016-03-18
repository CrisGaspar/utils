#include "bst.h"

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
