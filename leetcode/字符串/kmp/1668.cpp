
class Solution {
    public:
        int maxRepeating(string sequence, string word) {
            int k = 0;
            string s = word;
            while(sequence.find(s, 0) != -1){
                k++;
                s += word;
            }
            return k;
        }
    };