#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, s;
    cin >> n >> s;
    
    int a, b;
    cin >> a >> b;
    
    vector<pair<int, int>> apples; // 存储可摘苹果（高度，力气）
    
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        // 只保留能够到的苹果
        if (x <= a + b) {
            apples.push_back({y, x});
        }
    }
    
    sort(apples.begin(), apples.end());
    
    int count = 0;
    int remaining_s = s;
    
    for (const auto& apple : apples) {
        if (apple.first <= remaining_s) {
            remaining_s -= apple.first;
            count++;
        } else {
            break; 
        }
    }
    
    cout << count << endl;
    return 0;
}