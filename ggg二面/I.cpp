#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<pair<int,int> > nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i].first;
        nums[i].second = i+1;
    }
    sort(nums.begin(), nums.end());
    long long total_wait = 0;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        total_wait += sum;
        sum += nums[i].first;
    }
    double avg = (double)total_wait / n;
    
    for (int i = 0; i < n; i++) {
        cout << nums[i].second << " ";
    }
    cout << endl;
    printf("%.2f\n", avg);
    return 0;
}