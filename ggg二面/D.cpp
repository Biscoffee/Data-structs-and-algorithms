#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    unordered_map<int, int> s;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 1; i < n; i++) {
        int diff = abs(nums[i] - nums[i - 1]); //abs用于计算绝对值
        if (diff >= 1 && diff < n) {
            s[diff] = 1;  
        }
    }

    for (int i = 1; i < n; i++) {
        if (s.count(i) == 0) {
            cout << "Not jolly" << endl;
            return 0;
        }
    }

    cout << "Jolly" << endl;
    return 0;
}