class Solution {
    public:
        int maxSum(vector<int>& nums) {
            int n = nums.size();
            sort(nums.begin(), nums.end());
            unordered_map<int, int> cnt;
            for (int i = 0; i < n; i++) {
                cnt[nums[i]]++;
            }
            int ans = -1;
            
        }
    };