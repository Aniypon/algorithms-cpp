#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<int> a(n);
    for(int i=0; i<n; i++){
        cin >> a[i];
    }

    int exp_sum = (n+1)*(n+2)/2;

    int actual_sum =0;
    for (int num : a) {
        actual_sum += num;
    }

    int missing_number = exp_sum - actual_sum;
    cout << missing_number << endl;

    return 0;
}
