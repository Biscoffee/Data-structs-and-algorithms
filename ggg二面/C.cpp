#include <iostream>
using namespace std;
int main()
{
    double n;
    cin >> n;
    string s1;
    string s2;
    cin >> s1;
    cin >> s2;
    int cnt = 0;
    for(int i = 0; i < s1.size();i++){
        if(s1[i] == s2[i]){
            cnt++;
        }
    }
    double res = (double)cnt / s1.size();
    if(res >= n){
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}