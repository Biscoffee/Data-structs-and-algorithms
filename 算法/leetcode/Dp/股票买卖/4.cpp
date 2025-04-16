class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        // 如果交易次数远大于天数，退化为无限交易（贪心）
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; ++i)
                if (prices[i] > prices[i - 1])
                    profit += prices[i] - prices[i - 1];
            return profit;
        }

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2, 0)));

        for (int j = 0; j <= k; ++j) {
            dp[0][j][0] = 0;
            dp[0][j][1] = -prices[0]; // 如果允许 j 次交易，那么一开始就买了
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
            }
        }

        int maxProfit = 0;
        for (int j = 0; j <= k; ++j)
            maxProfit = max(maxProfit, dp[n - 1][j][0]);

        return maxProfit;
    }
};