class Solution {
    public:
        int maxArea(vector<int>& height) {
            int n = height.size();
            int sum[n] = {0};
            for(int i = 0;i < n;i++){
                sum[i] = sum[i - 1] + height[i];
            }
            
        }
    };