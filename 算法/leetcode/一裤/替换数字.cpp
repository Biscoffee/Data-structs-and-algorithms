#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;  
    string result;
        for (char c : s) {
        if (isdigit(c)) {  // 判断是否为数字
            result += "number";
        } else {
            result += c;
        }
    }
    
    cout << result << endl;
    return 0;
}