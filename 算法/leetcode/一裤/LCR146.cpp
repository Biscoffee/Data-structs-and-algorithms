class Solution {
    public:
        vector<int> spiralArray(vector<vector<int>>& array) {
            vector<int> result;
        if (array.empty() || array[0].empty()) return result;
    
        int m = array.size();        // 行数
        int n = array[0].size();     // 列数
    
        int top = 0, bottom = m - 1;
        int left = 0, right = n - 1;
    
        while (top <= bottom && left <= right) {
            // 从左到右
            for (int j = left; j <= right; ++j) {
                result.push_back(array[top][j]);
            }
            top++;
    
            // 从上到下
            for (int i = top; i <= bottom; ++i) {
                result.push_back(array[i][right]);
            }
            right--;
    
            // 从右到左（注意是否还存在这一行）
            if (top <= bottom) {
                for (int j = right; j >= left; --j) {
                    result.push_back(array[bottom][j]);
                }
                bottom--;
            }
    
            // 从下到上（注意是否还存在这一列）
            if (left <= right) {
                for (int i = bottom; i >= top; --i) {
                    result.push_back(array[i][left]);
                }
                left++;
            }
        }
    
        return result;
        }
    };