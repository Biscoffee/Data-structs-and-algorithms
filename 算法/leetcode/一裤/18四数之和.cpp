class Solution {
    public:
        vector<vector<int>> fourSum(vector<int>& nums, int target) {
            sort(nums.begin(), nums.end());
            int n = nums.size();
            vector<vector<int>> ans;
    
            for (int i = 0; i < n; i++) {
                if (i > 0 && nums[i] == nums[i - 1]) continue; // 跳过重复元素
    
                for (int j = i + 1; j < n; j++) {
                    if (j > i + 1 && nums[j] == nums[j - 1]) continue; // 跳过重复元素
    
                    int l = j + 1, r = n - 1;
                    while (l < r) {
                        long long s = (long long)nums[i] + nums[j] + nums[l] + nums[r]; // 避免溢出
    
                        if (s < target) l++; 
                        else if (s > target) r--;
                        else {
                            ans.push_back({nums[i], nums[j], nums[l], nums[r]});
    
                            // 先跳过重复元素
                            while (l < r && nums[l] == nums[l + 1]) l++;
                            while (l < r && nums[r] == nums[r - 1]) r--;
    
                            l++; 
                            r--;
                        }
                    }
                }
            }
            return ans;
        }
    };