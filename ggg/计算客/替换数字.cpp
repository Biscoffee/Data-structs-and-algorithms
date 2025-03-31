#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;  
    string s;
    for(auto c : s){
        if(isdigit(c)) {
            s += "number";
        } else {
            s += c;
        }
    }
    return 0;
}