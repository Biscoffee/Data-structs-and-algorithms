class Solution {
    public:
        int equalSubstring(string s, string t, int maxCost) {
            int cost = 0;
            int n = s.size();
            vector<int> costs(n, 0);
            for (int i = 0; i < n; i++) {
                costs[i] = abs(s[i] - t[i]);
            }
    
            int l = 0;
            int ans = 0;
    
            for (int r = 0; r < n; r++) {
                cost += costs[r];
                while (cost > maxCost) {
                    cost -= costs[l];
                    l++;
                }
                ans = max(ans, r - l + 1);
            }
            return ans;
        }
    };