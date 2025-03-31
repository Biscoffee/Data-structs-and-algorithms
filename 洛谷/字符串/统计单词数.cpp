#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

string toLower(const string& s) {
    string lower;
    for (char c : s) {
        lower += tolower(c);
    }
    return lower;
}

int main() {
    string word, article;
    getline(cin, word);
    getline(cin, article);
    
    string lowerWord = toLower(word);
    
    vector<string> words;
    string current;
    int pos = 0; 
    vector<int> positions; 
    
    // 分割文章为单词并记录位置
    for (char c : article) {
        if (c == ' ') {
            if (!current.empty()) {
                words.push_back(current);
                positions.push_back(pos - current.length());
                current.clear();
            }
            pos++;
        } else {
            current += c;
            pos++;
        }
    }

    if (!current.empty()) {
        words.push_back(current);
        positions.push_back(pos - current.length());
    }
    
    int count = 0, firstPos = -1;
    
    for (int i = 0; i < words.size(); ++i) {
        if (toLower(words[i]) == lowerWord) {
            count++;
            if (firstPos == -1) {
                firstPos = positions[i];
            }
        }
    }
    
    if (count > 0) {
        cout << count << " " << firstPos << endl;
    } else {
        cout << -1 << endl;
    }
    
    return 0;
}