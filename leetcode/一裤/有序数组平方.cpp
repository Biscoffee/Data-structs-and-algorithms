class Solution {
    public:
        vector<int> sortedSquares(vector<int>& nums) {
            int n = nums.size();
            vector<int> ans(n);
            int i = 0, j = n - 1;
            for(int p = n - 1;p >= 0; p--){
                int x = nums[i] * nums[i];
                int y = nums[j] * nums[j];
                if(x >= y){
                    ans[p] = x;
                    i++;
                } else {
                    ans[p] = y;
                    j--;
                }
            }
            return ans;
        }
    };