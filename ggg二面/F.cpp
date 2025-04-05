#include<iostream>
using namespace std;
int tentotwo(int n){
    int res = 0;
    int t = 1;
    while(n){
        res += (n % 2) * t;
        t *= 10;
        n /= 2;
    }
    return res;
}
bool AorB(int res){
    int cnt1 = 0;
    int cnt2 = 0;
    while(res){
        if(res % 10 == 1){
            cnt1++;
        } else {
            cnt2++;
        }
        res /= 10;
    }
    if(cnt1 > cnt2){
        return true;
    } else {
        return false;
    }
}
int main(){
    int n;
    cin >> n;
    int res = tentotwo(n);
    int cnta = 0;
    int cntb = 0;
    for(int i = 1; i <= n; i++){
        int temp = tentotwo(i);
        if(AorB(temp)){
            cnta++;
        } else {
            cntb++;
        }
    }
    cout << cnta << " " << cntb << endl;
    return 0;
}