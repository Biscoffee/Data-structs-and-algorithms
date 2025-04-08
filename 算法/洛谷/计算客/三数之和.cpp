#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n,k;
    cin >> n >> k;
    vector<int> nums(n);
    
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    sort(nums.begin(),nums.end());
    int ans = nums[0] + nums[1] + nums[2];
    for(int i = 0; i < n; i++){
        if(i > 0 && nums[i] == nums[i-1]) continue;
        int l = i+1;
        int r = n-1;
        while(l < r){
            int sum = nums[i] + nums[l] + nums[r];
            if(abs(sum - k) < abs(ans - k)){
                ans = sum;
            }
            if(sum > k) r--;
            else if(sum < k) l++;
            else{
                cout << k << endl;
                return 0;
            }
        }
    }
    cout << ans << endl;
    return 0;
}