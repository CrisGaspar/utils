#include <string>
#include <iostream>

using namespace std;

string reverse(string& s) {
    string st;
    for (auto& ch: s) {
        st.insert(0, 1, ch);
    }
    return st;
}

string reverse2(string& s) {
    string st;
    st.insert(st.begin(), s.rbegin(), s.rend());
    return st;
}

int main(int argc, char** argv) {
    string s("aedi");
    cout << reverse(s) << endl;
    cout << reverse2(s) << endl;
}

