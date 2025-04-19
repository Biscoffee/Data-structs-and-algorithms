class Solution {
    public:
        int trap(vector<int>& height) {
            int n = height.size();
            vector<int> head(n, 0);
            vector<int> tail(n, 0);
            head[0] = height[0];
            for (int i = 1; i < n; i++) {
                head[i] = max(head[i - 1], height[i]);
            }
            tail[n - 1] = height[n - 1];
            for (int i = n - 2; i >= 0; i--) {
                tail[i] = max(tail[i + 1], height[i]);
            }
            int ans = 0;
            for (int i = 0; i < n - 1; i++) {
                ans += min(head[i], tail[i]) -  height[i];
            }
            return ans;
        }
    };