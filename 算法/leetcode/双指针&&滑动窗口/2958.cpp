class Solution {
    public:
        bool isGood(vector<int>& nums, int l, int r) {
            int n = nums.size();
            unordered_map<int, int> freq;
            for (int i = l; i < r; i++) {
                if (++freq[nums[i]] > k) {
                    return false;
                }
            }
            return true;
        }
    
        int maxSubarrayLength(vector<int>& nums, int k) {
            int n = nums.size();
            int l = 0;
            int cur = 0;
            int ans = 0;
            for (int r = 0; r < n; r++) {
                if (isGood(nums, l, r)) {
                    cur = r - l + 1;
                } else {
                   while (!isGood(nums, l, r)) {
                        l++;
                    }
                    cur = r - l + 1;
                }
                ans = max(ans, cur);
            }

            return ans;
        }
    };