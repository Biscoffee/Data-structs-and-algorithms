#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;

    unordered_map<int, unordered_map<int, int>> storage;

    while (q--) {
        int op, i, j, k;
        cin >> op;
        if (op == 1) {
            cin >> i >> j >> k;
            storage[i][j] = k;
        } else {
            cin >> i >> j;
            cout << storage[i][j] << '\n';
        }
    }

    return 0;
}