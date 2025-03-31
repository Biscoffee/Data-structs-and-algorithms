#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    int a[10], k=0;
    string dc[] = {"one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty","a","both","another","first","second","third"};
    int dn[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,1,2,1,1,2,3};
    string s;
    for (int j=1; j<=6; j++) {
        cin >> s;
        for (int i=0; i<26; i++) {
            if (s==dc[i]) {  
                int x = dn[i];
                x = x * x % 100; 
                a[k++] = x;  
            }
        }
    }
 
    if (k==0) {
        cout << 0;
        return 0;
    }
    sort(a, a+k); 
    
    int st = 0;
    while (a[st]==0 && st<k) {
        st++;
    }
    printf("%d", a[st]);
    for (int i=st+1; i<k; i++) {
        printf("%02d", a[i]);
    }
    return 0;
}