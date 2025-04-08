class Solution {
    public:
        bool isPerfectSquare(int num) {
            int l = 0, r = num;
            int ans = 0;
            while(l <= r){
                long long int mid = l + (r - l)/2;
                long long int res = mid * mid;
                if(res == num){
                    return true;
                }
                if(res < num) l = mid + 1;
                else r = mid - 1;
            }
            return false;
        }
    };