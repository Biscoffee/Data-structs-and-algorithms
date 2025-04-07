#include <iostream>
#include <algorithm> // For max function

using namespace std;

int main() {
    int t, m;
    cin >> t >> m;
    int v[1010], w[1010];
    int dp[1010] = {0}; 

    for (int i = 0; i < m; i++) {
        cin >> v[i] >> w[i];
    }

    for (int i = 0; i < m; i++) {
        for (int j = t; j >= v[i]; j--) {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }

    cout << dp[t] << endl;
    return 0;
}