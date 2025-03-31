#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    stack<int> st;
    int num = 0;
    bool readingNum = false;

    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            readingNum = true;
        } else if (c == '.') {
            if (readingNum) {
                st.push(num);
                num = 0;
                readingNum = false;
            }
        } else if (c == '@') {
            break;
        } else {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            switch (c) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
            }
        }
    }
    
    cout << st.top() << endl;
    return 0;
}