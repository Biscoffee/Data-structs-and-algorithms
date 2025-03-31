#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<string> strs;
    string s;
    for (int i=0; i<n; i++) {
        cin >> s;
        strs.push_back(s);
    }
    sort(strs.begin(), strs.end(), [](string a, string b){return a+b>b+a;});
    for (auto s: strs) cout << s;
    return 0;
}