#include <iostream>
#include <vector>
#include <string>
using namespace std;

const vector<string> digitPatterns[10] = {
    {
        "XXX",
        "X.X",
        "X.X",
        "X.X",
        "XXX"
    },
    {
        "..X",
        "..X",
        "..X",
        "..X",
        "..X"
    },
    {
        "XXX",
        "..X",
        "XXX",
        "X..",
        "XXX"
    },
    {
        "XXX",
        "..X",
        "XXX",
        "..X",
        "XXX"
    },
    {
        "X.X",
        "X.X",
        "XXX",
        "..X",
        "..X"
    },
    {
        "XXX",
        "X..",
        "XXX",
        "..X",
        "XXX"
    },
    {
        "XXX",
        "X..",
        "XXX",
        "X.X",
        "XXX"
    },
    {
        "XXX",
        "..X",
        "..X",
        "..X",
        "..X"
    },
    {
        "XXX",
        "X.X",
        "XXX",
        "X.X",
        "XXX"
    },
    {
        "XXX",
        "X.X",
        "XXX",
        "..X",
        "XXX"
    }
};

int main() {
    int n;
    string number;
    cin >> n >> number;
    for (int row = 0; row < 5; ++row) {
        string line;
        for (char c : number) {
            int digit = c - '0';
            line += digitPatterns[digit][row];
            line += "."; 
        }

        if (!line.empty()) {
            line.pop_back();
        }
        cout << line << endl;
    }
    
    return 0;
}