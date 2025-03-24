#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> getNext(const vector<int>& p) {
        int n = p.size();
        vector<int> next(n + 1, -1); // next[0] = -1
        int i = 0, j = -1;
        while (i < n) {
            if (j == -1 || p[i] == p[j]) {
                i++;
                j++;
                next[i] = j;
            } else {
                j = next[j];
            }
        }
        return next;
    }

    int KMP1(const vector<int>& s, const vector<int>& p, const vector<int>& next) {
        int i = 0, j = 0;
        while (i < s.size()) {
            if (j == -1 || s[i] == p[j]) {
                i++;
                j++;
            } else {
                j = next[j];
            }
            if (j == p.size()) {
                return i;
            }
        }
        return -1;
    }

    bool canChoose(const vector<vector<int>>& groups, const vector<int>& nums) {
        int t = groups.size();
        int n = nums.size();
        vector<int> currentNums = nums; // 复制 nums，避免修改原数组

        for (int i = 0; i < t; i++) {
            vector<int> next = getNext(groups[i]);
            int x = KMP1(currentNums, groups[i], next);
            if (x == -1) {
                return false;
            } else {
                // 更新 currentNums 为剩余部分
                currentNums = vector<int>(currentNums.begin() + x, currentNums.end());
            }
        }
        return true;
    }
};