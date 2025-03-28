class Solution {
    public:
        vector<vector<int>> fourSum(vector<int>& nums, int target) {
            sort(nums.begin(), nums.end());
            int n = nums.size();
            vector<vector<int>> ans;
            for(int i = 0 ; i < n;i++){
                if(nums[i] > target && nums[i] >= 0 ) break;
                if(i > 0 && nums[i] == nums[i - 1]){
                    continue;
                }
                for(int j = i + 1; j < n; j++){
                    if(nums[i] + nums[j] > target && nums[i] + nums[j] >= 0) break;
                    if(j > i + 1 && nums[j] == nums[j - 1]){
                        continue;
                    }
                    int l = j + 1, r = n - 1;
                    while( l < r ){
                        int s = nums[i] + nums[j] + nums[l] + nums[r];
                        if(s < 0) l++;
                        else if(s > 0) r--;
                        else{
                            ans.push_back({nums[i],nums[j],nums[l],nums[r]});
                            while(l < r && nums[l] == nums[l+1]) l++;
                            while(l < r && nums[r] == nums[r - 1]) r--;
                            l++;
                            r--;
                        }
                    }
    
                }
            }
            return ans;
        }
    };