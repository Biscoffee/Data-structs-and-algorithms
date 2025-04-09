const int MODULO = 1000000007;

class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int> dp(high + 1);
        dp[0] = 1;
        for (int i = 1; i <= high; i++) {
            if (i >= zero) {
                dp[i] = (dp[i] + dp[i - zero]) % MODULO;
            }
            if (i >= one) {
                dp[i] = (dp[i] + dp[i - one]) % MODULO;
            }
        }
        int total = 0;
        for (int i = low; i <= high; i++) {
            total = (total + dp[i]) % MODULO;
        }
        return total;
    }
};
