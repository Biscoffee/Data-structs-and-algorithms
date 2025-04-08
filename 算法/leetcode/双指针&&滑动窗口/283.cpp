class Solution {
    public:
        void moveZeroes(vector<int>& nums) {
            int n = nums.size();
            int left = 0, right = n - 1;
            while(left <= right){
                if(nums[left] == 0){
                    for(int i = left; i < right; i++){
                        nums[i] = nums[i + 1];
                    }
                    nums[right] = 0;
                    right--;
                }else{
                    left++;
                }
            }
            return;
        }
    };