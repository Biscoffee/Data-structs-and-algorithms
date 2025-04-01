#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n,m;
    cin >> n >> m;
    vector<int> nums(m);
    for(int i = 0; i < m ; i++){
        cin >> nums[i];
        nums[i]--;
    }
    vector<int>lamp(n,0);
    for(int i = 0 ; i < m; i++){
        lamp[nums[i]]++;
        lamp[(nums[i] + n- 1) % n]++;
        lamp[(nums[i] + 1) % n]++;
    }
    for(int i = 0; i < n ; i++){
        if(lamp[i]% 2 == 1)  cout << "1 ";
        else cout << "0 ";
    }
    return 0;
}