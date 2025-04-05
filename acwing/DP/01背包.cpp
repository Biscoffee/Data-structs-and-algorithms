#include <iostream>
using namespace std;

int main() {
    int n,m;
    int v[1010],w[1010];
    int dp[1010][1010];
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        cin >> v[i] >> w[i];
    }
    for(int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= v[i]) dp[i][j] = max(dp[i][j], dp[i-1][j-v[i]] + w[i]);
        }
    }
    cout << dp[n][m];

    return 0; 
}