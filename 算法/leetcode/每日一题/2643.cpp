class Solution {
    public:
        vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
            vector<int> ans(2);
            int cnt = 0;
            int m = mat.size();
            int n = mat[0].size();
            for(int i = 0;i < m;i++){
                for(int j = 0;j < n;j++){
                    if(mat[i][j] == 1){
                       cnt ++;
                    }
                }
                if(cnt > ans[1]){
                    ans[0] = i;
                    ans[1] = cnt;
                    cnt = 0;
                }else{
                    cnt = 0;
                }
            }
            return ans;
        }
    };