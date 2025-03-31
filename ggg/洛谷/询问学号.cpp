#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>

using namespace std;

int main(){
    int n,m;
    cin >> n >> m;
    vector<int> nums(n);
    for(int i = 0;i < n;i++){
        cin >> nums[i];
    }
    vector<int> stu(m);
    for(int i = 0;i < m;i++){
        cin >> stu[i];
    }
    for(int i = 0;i < m;i++){
        cout << nums[stu[i] - 1] << endl;
    }
    return 0;
}