#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    long long sum = 0;
    multiset<int> window;

    for (int l = 0; l <= n - k; ++l) {
        window.clear();
        for (int r = l; r < n; ++r) {
            window.insert(a[r]);
            if (r - l + 1 >= k) {
                auto it = window.end();
                advance(it, -k);
                sum += *it;
            }
        }
    }

    cout << sum << endl;
    return 0;
}