#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 2, vector<char>(m + 2));
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            cin >> a[i][j];
    for(int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <= m; j ++ )
        {
            if(a[i][j] == '*')
            {
                cout << '*';
                continue;
            }
            int cnt = 0;
            for (int x = i - 1; x <= i + 1; x ++ )
                for (int y = j - 1; y <= j + 1; y ++ )
                    if(a[x][y] == '*')
                        cnt ++ ;
            cout << cnt;
        }
        cout << endl;
    }
    return 0;
}