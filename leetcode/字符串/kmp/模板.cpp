class Solution {
    public:
        vector<int> buildNext(const string& needle) {
            int n = needle.size();
            vector<int> next(n, 0);
            int j = 0;
            for (int i = 1; i < n; i++) {
                while (j > 0 && needle[i] != needle[j]) {
                    j = next[j]; // 直接跳转
                }
                if (needle[i] == needle[j]) {
                    j++;
                }
                next[i] = j;
            }
            return next;
        }
    
        int strStr(string haystack, string needle) {
            int n = haystack.size(), m = needle.size();
            if (m == 0) return 0;
            vector<int> next = buildNext(needle);
            int j = 0;
            for (int i = 0; i < n; i++) {
                while (j > 0 && haystack[i] != needle[j]) {
                    j = next[j]; // 直接跳转
                }
                if (haystack[i] == needle[j]) {
                    j++;
                }
                if (j == m) {
                    return i - m + 1;
                }
            }
            return -1;
        }
    };