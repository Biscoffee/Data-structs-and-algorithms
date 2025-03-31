#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> multiply(const vector<int>& A, const vector<int>& B) {
    vector<int> result(A.size() + B.size(), 0);
    for (int i = 0; i < A.size(); ++i) {
        int carry = 0;
        for (int j = 0; j < B.size() || carry; ++j) {
            long long current = result[i + j] + (long long)A[i] * (j < B.size() ? B[j] : 0) + carry;
            result[i + j] = current % 10; 
            carry = current / 10;  
        }
    }
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    int len1 = s1.size(), len2 = s2.size();
    vector<int> A(len1), B(len2);
    for (int i = 0; i < len1; i++) A[i] = s1[len1 - 1 - i] - '0';
    for (int i = 0; i < len2; i++) B[i] = s2[len2 - 1 - i] - '0';
    vector<int> C = multiply(A, B);
    for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
    cout << endl;

    return 0;
}