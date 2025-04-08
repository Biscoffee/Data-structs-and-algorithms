class Solution {
    public:
        int mySqrt(int x) {
            if (x == 0 || x == 1) return x; // 特殊情况处理
    
            int left = 0, right = x;
            int result = 0;
    
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if ((long long)mid * mid <= x) { // 防止溢出
                    result = mid; // 更新结果
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
    
            return result;
        }
    };
    