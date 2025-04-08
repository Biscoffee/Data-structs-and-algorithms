#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int N;
    cin >> N;
    for (int i = 1; i * i <= N; i++) {
        cout << i * i << " ";
    }
    cout << endl;
    return 0;
}