class Solution {
    public:
        long long maximumTripletValue(vector<int>& nums) {
            long long ans = 0;
            int max_diff = 0, pre_max = 0;
            for (int x : nums) {
                ans = max(ans, 1LL * max_diff * x);
                max_diff = max(max_diff, pre_max - x);
                pre_max = max(pre_max, x);
            }
            return ans;
        }
    };
    