


#include <iostream>

using namespace std;

int n,m;
int v[N],w[N],s[N];
int f[N][N];

int main()
{
    cin >> n >> m;

    for(int i = 1;i <= n;i++)  cin >> v[i] >> w[i] >> s[i];

    for(int i = 0;i <= n;i++)
    {
        for(int j = 0;j <= m;j++)
        {
            for(int k = 0;k <= s[i] && k * v[i];k++)  
            {
                f[i][j] = max(f[i][j],f[i - 1][j - k * v[i] + k * w[i]]);
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}
