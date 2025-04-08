#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> nums;
    int i = 0;
    do {
        scanf("%d", &nums[i]);
        i++;
    }while(nums[i - 1] != 0);
    
    reverse(nums.begin(), nums.end());
    
    int n = nums.size();
    for (int j = 0; j < n; j++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    return 0;
}