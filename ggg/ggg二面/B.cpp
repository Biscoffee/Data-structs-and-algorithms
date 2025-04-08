#include<iostream>
using namespace std;
bool ishui(int n){
    int a[10];
    int i = 0;
    while(n){
        a[i++] = n % 10;
        n /= 10;
    }
    for(int j = 0; j < i / 2; j++){
        if(a[j] != a[i - j - 1]) return false;
    }
    return true;
}
bool isPrime(int n)
{
    if(n < 2) return false;
    for(int i = 2; i <= n / i; i++)
    {
        if(n % i == 0) return false;
    }
    return true;
}
int main()
{
    int n;
    int cnt = 0;
    cin >> n;
    for(int i = 11; i <= n;i++){
        if(ishui(i) && isPrime(i)){
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}