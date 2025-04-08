#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> counts(26, 0);
    string line;
    
    for (int i = 0; i < 4; ++i) {
        getline(cin, line);
        for (char c : line) {
            if (c >= 'A' && c <= 'Z') {
                counts[c - 'A']++;
            }
        }
    }
    
    int max_height = *max_element(counts.begin(), counts.end());
    
    for (int row = max_height; row > 0; --row) {
        string line_output;
        for (int i = 0; i < 26; ++i) {
            if (counts[i] >= row) {
                line_output += "* ";
            } else {
                line_output += "  ";
            }
        }
        while (!line_output.empty() && line_output.back() == ' ') {
            line_output.pop_back();
        }
        cout << line_output << endl;
    }
    
    string letters;
    for (char c = 'A'; c <= 'Z'; ++c) {
        letters += c;
        letters += ' ';
    }
    if (!letters.empty()) {
        letters.pop_back();
    }
    cout << letters << endl;
    
    return 0;
}