#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool check(const vector<int>& nums, int m, long long max_sum) {
    long long current_sum = 0;
    int segments = 1; 
    
    for (int num : nums) {
        if (current_sum + num > max_sum) {
            segments++;
            current_sum = num;
            if (segments > m) return false;
        } else {
            current_sum += num;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> nums(n);
    long long left = 0, right = 0;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        if (nums[i] > left) left = nums[i];
        right += nums[i];
    }
    
    long long answer = right;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (check(nums, m, mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    cout << answer << endl;
    return 0;
}