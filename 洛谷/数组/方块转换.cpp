#include <iostream>
#include <vector>
using namespace std;

typedef vector<string> Pattern;


Pattern rotate90(const Pattern& p) {
    int n = p.size();
    Pattern rotated(n, string(n, ' '));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            rotated[j][n-1-i] = p[i][j];
        }
    }
    return rotated;
}


Pattern reflect(const Pattern& p) {
    int n = p.size();
    Pattern reflected = p;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n/2; ++j) {
            swap(reflected[i][j], reflected[i][n-1-j]);
        }
    }
    return reflected;
}

bool isSame(const Pattern& a, const Pattern& b) {
    return a == b;
}

int main() {
    int n;
    cin >> n;
    
    Pattern original(n), target(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> original[i];
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> target[i];
    }
    
    Pattern transformed;
    
    transformed = rotate90(original);
    if (isSame(transformed, target)) {
        cout << "1" << endl;
        return 0;
    }
    
    transformed = rotate90(transformed);
    if (isSame(transformed, target)) {
        cout << "2" << endl;
        return 0;
    }
    
    transformed = rotate90(transformed);
    if (isSame(transformed, target)) {
        cout << "3" << endl;
        return 0;
    }
    
    transformed = reflect(original);
    if (isSame(transformed, target)) {
        cout << "4" << endl;
        return 0;
    }
    

    for (int i = 1; i <= 3; ++i) {
        transformed = rotate90(transformed);
        if (isSame(transformed, target)) {
            cout << "5" << endl;
            return 0;
        }
    }

    if (isSame(original, target)) {
        cout << "6" << endl;
        return 0;
    }

    cout << "7" << endl;
    return 0;
}