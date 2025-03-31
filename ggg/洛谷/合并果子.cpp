#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int ans = 0;
    sort(nums.begin(), nums.end());
    vector<int> sum(n,0);
    sum[0] = nums[0];
    for(int i = 1; i < n;i++){
        sum[i] = sum[i - 1] + nums[i];
    }
    cout << sum[n - 1] << endl;
    return 0;
}