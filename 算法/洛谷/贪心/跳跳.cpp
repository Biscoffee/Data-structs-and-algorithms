#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    sort(h.begin(), h.end());
    
    long long total = 0;
    int left = 0, right = n - 1;
    int last = 0; 
    
    bool turn = true; 
    
    while (left <= right) {
        int current;
        if (turn) {
            current = h[right];
            right--;
        } else {
            current = h[left];
            left++;
        }
        total += (current - last) * (current - last);
        last = current;
        turn = !turn;
    }
    
    cout << total << endl;
    return 0;
}