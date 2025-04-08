#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    
    n %= 26; // 处理n大于26的情况
    
    for (char &c : s) {
        // 计算移动后的字符
        c = 'a' + (c - 'a' + n) % 26;
    }
    
    cout << s << endl;
    return 0;
}