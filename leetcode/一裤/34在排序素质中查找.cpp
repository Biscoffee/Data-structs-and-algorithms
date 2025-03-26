class Solution {
    public:
        int search1(vector<int>& nums, int target) {
            int n = nums.size();
            int l = 0, r = n - 1;  
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (nums[mid] < target)  
                    l = mid + 1;
                else 
                    r = mid - 1;
            }
            return l;
        }
    
        int search2(vector<int>& nums, int target) {
            int n = nums.size();
            int l = 0, r = n - 1;  
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (nums[mid] > target)  
                    r = mid - 1;
                else 
                    l = mid + 1;
            }
            return r;
        }
    
        vector<int> searchRange(vector<int>& nums, int target) {
            if (nums.empty()) return {-1, -1};  
    
            int l = search1(nums, target);
            int r = search2(nums, target);
    
            // 确保找到的是 target 范围内的索引
            if (l <= r && l < nums.size() && nums[l] == target)  
                return {l, r};  
            else  
                return {-1, -1};  
        }
    };