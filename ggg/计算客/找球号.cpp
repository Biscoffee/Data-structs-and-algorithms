#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool isfind(vector<int> a,int x){
    int n = a.size();
    int l = 0, r = n - 1;
    while(l <= r){
        int mid = l + (r - l) / 2;
        if(a[mid] == x){
            return true;
        } else if(a[mid] > x){
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return false;
}
int main()
{
    int m,n;
    cin >> m >> n ;
    vector<int>a (m);
    for(int i = 0;i < m;i++){
        cin >> a[i];
    }
    int b[n];
    for(int i = 0; i < n ; i++){
        cin >> b[i];
    }
    for(int i = 0; i < n;i++){
        if(isfind(a,b[i])){
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}