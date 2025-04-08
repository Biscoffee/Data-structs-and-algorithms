#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
string reverseNum(string s) {
    reverse(s.begin(), s.end());
    
    size_t pos = s.find_first_not_of('0');
    if (pos != string::npos) {
        s = s.substr(pos);
    } else {
        s = "0";
    }
    
    return s;
}

string reverseDecimal(string s) {
    reverse(s.begin(), s.end());
    
    size_t pos = s.find_last_not_of('0');
    if (pos != string::npos) {
        s = s.substr(0, pos + 1);
    } else {
        s = "0";
    }
    
    return s;
}

int main() {
    string s;
    cin >> s;
    
    size_t dotPos = s.find('.');
    size_t slashPos = s.find('/');
    size_t percentPos = s.find('%');
    
    if (dotPos != string::npos) {
        string integerPart = s.substr(0, dotPos);
        string decimalPart = s.substr(dotPos + 1);
        
        string reversedInteger = reverseNum(integerPart);
        string reversedDecimal = reverseDecimal(decimalPart);
        
        cout << reversedInteger << "." << reversedDecimal << endl;
    } else if (slashPos != string::npos) {
        string numerator = s.substr(0, slashPos);
        string denominator = s.substr(slashPos + 1);
        
        string reversedNumerator = reverseNum(numerator);
        string reversedDenominator = reverseNum(denominator);
        
        cout << reversedNumerator << "/" << reversedDenominator << endl;
    } else if (percentPos != string::npos) {
        string number = s.substr(0, percentPos);
        string reversedNumber = reverseNum(number);
        
        cout << reversedNumber << "%" << endl;
    } else {

        string reversedNumber = reverseNum(s);
        cout << reversedNumber << endl;
    }
    
    return 0;
}