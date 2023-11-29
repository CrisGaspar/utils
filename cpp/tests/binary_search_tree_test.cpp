#include <string>
#include <functional>
#include <cassert>

#include "../include/binary_search_tree.h"

struct Spaceship {
    // ... omitting parameters
    string name;

    Spaceship(const string& iName) : name(iName) {}

    // Conversion operator override: use as key in my Binary-Search-Tree implementation
    operator const string&() const {
        return name;
    }
};

// overload << for cout
ostream& operator << (ostream& out, const Spaceship& ship) { return out << ship.name; }

void testBSTInt() {
    auto coutf = [] (const int& i) { cout << i << " "; };
    vector<int> vals = { 5, 10, 2, 11, 4, 9, 12, 1, 2, 3};

    efficient::Node<int>* root = efficient::createBST<int, int>(vals);

    unordered_set<efficient::Node<int>*> visited;

    cout << "Breadth first search: ";
    efficient::bfs(root, visited, coutf);
    cout << endl;

    visited.clear();
    cout << "Depth first search: ";
    efficient::dfs(root, visited, coutf);
    cout << endl;

    clearBST(root);
}

void testBSTSpaceship() {
    auto coutf = [] (const Spaceship& s) { cout << s << " "; };

    vector<Spaceship> vals = {
        Spaceship("Enterprise"),
        Spaceship("Galactica"),
        Spaceship("Daedalus"),
        Spaceship("SpaceshipOne"),
        Spaceship("DeathStar"),
        Spaceship("Discovery"),
    };

    efficient::Node<Spaceship>* root = efficient::createBST<Spaceship, string>(vals);

    unordered_set<efficient::Node<Spaceship>*> visited;

    cout << "Breadth first search: ";
    efficient::bfs(root, visited, coutf);
    cout << endl;

    visited.clear();
    cout << "Depth first search: ";
    efficient::dfs(root, visited, coutf);
    cout << endl;

    auto name = "Discover";
    auto node = efficient::find<Spaceship, string>(root, name);
    assert(node == nullptr);

    name = "Discovery";
    node = efficient::find<Spaceship, string>(root, name);
    assert(node != nullptr && (node->elem.name == name));

    clearBST(root);
}

int main(int argc, char** argv) {
    testBSTInt();
    testBSTSpaceship();
    return 0;
}
