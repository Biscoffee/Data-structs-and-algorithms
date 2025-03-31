#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    string word;
    cin >> word;
    
    vector<int> freq(26, 0); 

    for (char c : word) {
        freq[c - 'a']++;
    }
    

    int maxn = 0, minn = 100; 
    for (int count : freq) {
        if (count > 0) { 
            if (count > maxn) maxn = count;
            if (count < minn) minn = count;
        }
    }
    
    int diff = maxn - minn;
    
    if (isPrime(diff)) {
        cout << "Lucky Word" << endl;
        cout << diff << endl;
    } else {
        cout << "No Answer" << endl;
        cout << 0 << endl;
    }
    
    return 0;
}