class Solution {
    public:
        int longestConsecutive(vector<int>& nums) {
            unorded_set<int> us;
            for(const int& num : nums) {
                us.insert(num);
            }
            int longestStreak = 0;
            for(const int& num : us) {
                if (!us.count(num - 1)) {  // 没有前驱,判断是不是起点
                    int currentNum = num;
                    int currentStreak = 1;
                    while (us.count(currentNum + 1)) {
                        currentNum += 1;
                        currentStreak += 1;
                    }
                    longestStreak = max(longestStreak,currentStreak);
                }
            }
            return longestStreak;
        }
    };