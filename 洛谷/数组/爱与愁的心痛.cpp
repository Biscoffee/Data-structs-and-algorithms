#include <stdio.h>
#define MAX 100001
int main(int argc, const char * argv[]) {
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d\n",&a[i]);
    }
    int min = 0;
    for (int i = 0; i <= n-m; i++)
    {
        int sum = 0;
        for (int j = i; j < i+m; j++) {
            sum += a[j];
        }
        if (sum < min || min == 0) {
            min = sum;
        }
    }
    printf("%d",min);
}
