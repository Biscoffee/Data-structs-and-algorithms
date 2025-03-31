#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> add(vector<int>& nums1, vector<int>& nums2) {
    if(nums1.size() < nums2.size()) return add(nums2, nums1);
    vector<int> c;
    int t = 0;
    for (int i = 0; i < nums1.size(); i++) {
        t += nums1[i];
        if(i < nums2.size()) t += nums2[i];
        c.push_back(t % 10);
        t /= 10;
    }
    if(t) c.push_back(t);
    return c;
}
int main() {
    string s1, s2;
    cin >> s1 >> s2;
    vector<int> nums1, nums2;
    for(int i = 0; i < s1.size(); i++) {
        nums1.push_back(s1[i] - '0');
    }
    for(int i = 0; i < s2.size(); i++) {
        nums2.push_back(s2[i] - '0');
    }
    reverse(nums1.begin(), nums1.end());
    reverse(nums2.begin(), nums2.end());
    vector<int> res = add(nums1, nums2);
    reverse(res.begin(), res.end());
    for(int i = 0; i < res.size(); i++) {
        printf("%d", res[i]);
    }
    return 0;
}