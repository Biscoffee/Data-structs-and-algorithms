class Solution {
    public:
        int trap(vector<int>& height) {
            int ans = 0;
            for(int i = 0; i < n;i++) {
                if(h == 0 && height[i - 1] && height[i + 1])  {
                    ans += min(height[i- 1],height[i + 1]);
                    continue;
                }
                int left = ,right = height.size() - 1;
                int leftMax = 0,rightMax = 0;
            }
        }
    };