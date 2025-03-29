#include <vector>
using namespace std;

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    int num = 1;
    int layer = (n + 1) / 2;  

    for (int l = 0; l < layer; l++) {
        for (int i = l; i < n - l; i++) {
            matrix[l][i] = num++;
        }
        for (int i = l + 1; i < n - l; i++) {
            matrix[i][n - l - 1] = num++;
        }
        if (l < n - l - 1) {
            for (int i = n - l - 2; i >= l; i--) {
                matrix[n - l - 1][i] = num++;
            }
        }

        if (l < n - l - 1) {
            for (int i = n - l - 2; i > l; i--) {
                matrix[i][l] = num++;
            }
        }
    }
    return matrix;
}