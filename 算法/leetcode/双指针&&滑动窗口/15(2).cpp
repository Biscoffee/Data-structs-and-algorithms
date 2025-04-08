
class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            int n = nums.size();
            sort(nums.begin(),nums.end());
            vector<vector<int>> ans;
            for(int i = 0;i < n;i++){
                int l = i + 1;
                int r = n - 1;
                if (i > 0 && nums[i] == nums[i - 1]) {
                    continue;
                }
                while (l < r) {
                    if (nums[i] + nums[l] + nums[r] == 0) {
                        ans.push_back({nums[i],nums[l],nums[r]});
                        while (l < r && nums[l] == nums[l + 1]) {
                            l++;
                        }
                        l++;
                        while (l < r && nums[r] == nums[r - 1]) {
                            r--;
                        }
                        r--; 
                    }
                    else if (nums[i] + nums[l] + nums[r] > 0) {
                        r--;
                    }
                    else {
                        l++;
                    }
                }
            }
            return ans;
        }
    };