#include <iostream>
#include <vector>
using namespace std;


class solution 
{
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (nums[mid] <= target) l = mid+1;
            else r = mid - 1;
        }
        return l;
    }
};