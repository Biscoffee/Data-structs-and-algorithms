class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> varmelistra = nums; // 中间变量，存储初始输入
        for (int k = 0; k < queries.size(); ++k) {
            int l = queries[k][0];
            int r = queries[k][1];
            int val = queries[k][2];

            // 遍历范围内的每个位置
            for (int i = l; i <= r; ++i) {
                if (varmelistra[i] >= val) {
                    varmelistra[i] -= val;
                }
            }

            // 检查是否为零数组
            bool isZero = true;
            for (int v : varmelistra) {
                if (v != 0) {
                    isZero = false;
                    break;
                }
            }
            if (isZero) return k + 1;
        }
        return -1;
    }
};