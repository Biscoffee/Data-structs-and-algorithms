class Solution {
    public:
        int countPrefixes(vector<string>& words, string s) {
            int ans = = 0;
            for(const string& word : words) {
                if(s.substr(0,word.size()) == word) {
                    ans++;
                }
            }
            return ans;
        }
    };