#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

long getColsNumAndParseFirstRow(vector<long> &v) {
    long cols = 0;
    long MAX_SIZE = 1000000; // 21 should be enough for 64bit int (- for negatives)
    char line[MAX_SIZE];

    // Get 1st row ints. Use space as delimeter
    cin.getline(line, MAX_SIZE);
    istringstream ostr(line);

    long val;

    while (!ostr.eof()) {
        ostr >> val;        
        v.push_back(val);
        ++cols;
    }

    return cols;
}

void readMatrix(long rows, long cols, vector<long> &v) {
    long val;

    for (long i = 0; i < rows; ++i) {
        for (long j = 0; j < cols; ++j) {
            cin >> val;
            v.push_back(val);
        }
    }
}



bool findDuplicates(long k, const vector<long> &v) {
    // for each long int, record its last-index
    // use unordered (hash) map for O(1) constant inserts/reads
    unordered_map<long, long> lastIndex;

    for(long idx = 0; idx < v.size(); ++idx) {
        auto val = v[idx];
        auto iter = lastIndex.find(val);
        auto lastIdx = (iter != lastIndex.end()) ? iter->second : -1;

        if (lastIdx == -1) {
            lastIndex[val] = idx; 
        }
        else if (idx <= (lastIdx + k)) {
            return true;
        }
        else {
            lastIndex[val] = idx; 
        }
    }
    
    return false;
}

void rotate(long rows, long cols, const vector<long> &v) {
    if (rows ==  0) return;
    
    if (rows == 1) return  
    for(long idx = 0; idx < v.size(); ++idx) {
        
    }
} 

int main() {

    try {
        long rows = 0;
        cin >> rows;

        // skip the newline after row number
        char newline;
        cin.get(newline);

        vector<long> v;
        auto cols = getColsNumAndParseFirstRow(v); 

        cout << "Rows: " << rows << " cols: " << cols << endl;
    
        // read all other rows
        readMatrix(rows - 1, cols, v);

        long k;
        cin >> k;

        cout << (findDuplicates(k, v) ? "YES" : "NO") << endl;
    }
    catch (exception& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
    
    return 0;
}
