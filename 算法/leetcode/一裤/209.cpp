class Solution {
    public:
        int minSubArrayLen(int target, vector<int>& nums) {
            int n = nums.size();
            int l = 0;
            int ans = n + 1;
            int sum = 0;
            for(int r = 0;r < n;r++){
                sum += nums[r];
                while(sum - nums[l] >= target){
                    sum -= nums[l];
                    l++;
                }
                if(sum >= target){
                    ans = min(ans , r - l + 1);
                }
            }
            return ans<=n ? ans : 0;
        }
    };