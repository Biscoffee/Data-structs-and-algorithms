class Solution {
    public:
        void moveZeroes(vector<int>& nums) {
            int i0 = 0;
            for (int& x : nums) { // 注意 x 是引用
                if (x) {
                    swap(x, nums[i0]);
                    i0++;
                }
            }
        }
    };