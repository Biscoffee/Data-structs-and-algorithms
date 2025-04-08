class Solution {
    public:
        bool rotateString(string s, string goal) {
            int n = s.size(), m = goal.size();
            if (n != m) return false;
            goal += goal;
            return goal.find(s) != string::npos;
        }
    };


    class Solution {
        public:
            bool rotateString(string s, string goal) {
                int n = s.size(), m = goal.size();
                if (n != m) return false;
                goal += goal;
                m += m;
                vector<int> next(n , 0);
                int j = 0;
                for(int i = 1;i < n; i++){
                    while(j > 0 && s[i] != s[j]){
                        j = next[j - 1];
                    }
                    if(s[i] == s[j])  j++;
                    next[i] = j;
                }
                int k = 0;
                for(int i = 0; i < m;i++){
                    while(k > 0 && goal[i] != s[k]){
                        k = next[k - 1];
                    }
                    if(goal[i] == s[k]) k++;
                    if(k == n) return true;
                }
                return false;
            }
        };