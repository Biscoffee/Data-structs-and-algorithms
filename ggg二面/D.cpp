#include <iostream>
#include<vector>
using namespace std;
int main()
{
    unordered_map<int,int> s;
    int n;
    cin >> n;
    vector<int>nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    for(int i = 1;i <= n;i++){
        s[i] = 1;
    }
    for(int i = 0; i < n;i++){
        if(s.count(nums[i])){
            s[nums[i]]--;
        }
    }
    for(auto i : s){
        if(i.second == 1){
            cout << "Not jolly" << endl;
            return 0;
        }
    }
    cout << "Jolly" << endl;
    return 0;
}