#include <iostream>
using namespace std;

int main(){
    string s;
    cin >> s;
    int num[26];
    for (int i = 0; i < 26; i++){
        num[i] = 0;
    }
    for (int i = 0; i < s.size(); i++){
        num[s[i] - 'a']++;
    }
    for(char c : s){
        if(num[c-'a'] == 1){
            cout << c << endl;
            return 0;
        }
    }
    cout << "no" << endl;
    return 0;
}
