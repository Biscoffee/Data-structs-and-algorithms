#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    
    unordered_set<int> sums;
    unordered_set<int> counted;
    int result = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            sums.insert(nums[i] + nums[j]);
        }
    }
    
    for (int num : nums) {
        if (sums.count(num) && !counted.count(num)) {
            result++;
            counted.insert(num);
        }
    }
    
    cout << result << endl;
    return 0;
}