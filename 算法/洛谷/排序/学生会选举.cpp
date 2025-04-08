#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n,m;
    cin >> n >> m;
    vector<int> nums(n);
    for (int i=0; i<n; i++) cin >> nums[i];
    sort(nums.begin(), nums.end());
    for(auto num: nums) cout << num << " ";
    return 0;
}