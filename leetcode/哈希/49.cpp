class Solution {
    public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
            unordered_map<string,vector<string>> hash; 
            int n = strs.size();
            for(int i = 0; i < n; i++){ 
                string temp = strs[i];
                sort(temp.begin(),temp.end()); 
                hash[temp].push_back(strs[i]); 
            }
            vector<vector<string>> ret;
            for(auto it = hash.begin(); it != hash.end(); it++){ 
                ret.push_back(it->second);
            }
            return ret;
        }
    };
   