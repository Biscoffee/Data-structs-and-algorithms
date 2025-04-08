class Solution {
    public:
        bool repeatedSubstringPattern(string s) {
            string temp = s+ s;
            temp.erase(temp.begin());
            temp.erase(temp.end()-1);
            if(temp.find(s) != string :: npos) return true;
            return false;
        }
    };