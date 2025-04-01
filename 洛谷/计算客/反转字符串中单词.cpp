class Solution {
    public:
       string reverseWords(string s) {
           std::vector<std::string> wordsVector;
           int i, j;
           i = s.size() - 1;
           j = i;
    
           while (i >= 0) {
               while (i >= 0 && s[i] != ' ')
                   i--;
    
               if (i != j)
                   wordsVector.push_back(s.substr(i + 1, (j - i)));
    
               while (i >= 0 && s[i] == ' ') {
                   i--;
                   j = i;
               }
           }
    
           std::string result;
           for (int n = 0; n < wordsVector.size(); ++n) {
               result += wordsVector[n];
               if (n != wordsVector.size() - 1)
                   result += ' ';
           }
    
           return result;
       }
    };