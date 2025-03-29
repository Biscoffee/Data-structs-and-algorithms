#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    vector<int> s(100005);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int l = 0;
    int res = 0;
    for(int r = 0; r < n; r++) {
        s[nums[r]]++;
        while(s[nums[r]]){
            s[nums[l]]--;
            l++;
        }
        res = max(res, r - l + 1);
    }
    cout << res << endl;
    return 0;
}