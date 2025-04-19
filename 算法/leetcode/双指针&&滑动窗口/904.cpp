#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> fruit_count;
        int left = 0;
        int max_fruits = 0;
        
        for (int right = 0; right < fruits.size(); ++right) {
            fruit_count[fruits[right]]++;
            
            // 如果水果类型超过2种，移动左指针
            while (fruit_count.size() > 2) {
                fruit_count[fruits[left]]--;
                if (fruit_count[fruits[left]] == 0) {
                    fruit_count.erase(fruits[left]);
                }
                left++;
            }
            
            // 更新最大水果数量
            max_fruits = max(max_fruits, right - left + 1);
        }
        
        return max_fruits;
    }
};