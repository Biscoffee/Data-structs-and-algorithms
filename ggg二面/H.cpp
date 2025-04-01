#include<iostream>
#include <vector>
using namespace std;

int main()
{
    int n,m;
    cin >> n >> m;
    vector<int>nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    vector<int>ask(m);
    for(int i = 0; i < m; i++){
        cin >> ask[i];
    }
    for(int i = 0; i < m; i++){
        int l = 0;
        int r = n - 1;
        while(l < r){
            int mid = l + r >> 1;
            if(nums[mid] >= ask[i]){
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        if(nums[l] == ask[i]){
            cout << l + 1 << " ";
        } else {
            cout << -1 << " ";
        }
    }
    return 0;
}