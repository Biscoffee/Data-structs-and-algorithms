class Solution {
    public:
        string decodeString(string s) {
        stack<int> countStack;
        stack<string> stringStack;
        string currentString = "";
        int currentNum = 0;
    
        for (char ch : s) {
            if (isdigit(ch)) {
                currentNum = currentNum * 10 + (ch - '0');  // 多位数
            } else if (ch == '[') {
                countStack.push(currentNum);
                stringStack.push(currentString);
                currentNum = 0;
                currentString = "";
            } else if (ch == ']') {
                string prevString = stringStack.top(); stringStack.pop();
                int repeatTimes = countStack.top(); countStack.pop();
                string temp = "";
                for (int i = 0; i < repeatTimes; ++i) {
                    temp += currentString;
                }
                currentString = prevString + temp;
            } else {
                currentString += ch;
            }
        }
    
        return currentString;
    }
    };