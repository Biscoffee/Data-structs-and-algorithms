#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> nums(n);
    unordered_set<int> s;
    for (int i=0; i<n; i++) {
        cin >> nums[i];
        s.insert(nums[i]);
    }
    int ans = s.size();
    cout << ans << endl;
    vector<int> vec(s.begin(), s.end());
    sort(vec.begin(), vec.end());
    for (int num : vec) {
        cout << num << " ";
    }
    
    return 0;
}