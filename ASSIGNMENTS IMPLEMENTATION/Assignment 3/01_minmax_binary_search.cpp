#include <bits/stdc++.h>
using namespace std;
pair<long long,  long long > findMinMax(const vector<long long> & a,  int l,  int r) {
    if (l == r) return {
        a[l],  a[l]
    };
    if (r == l + 1) return {
        min(a[l],  a[r]),  max(a[l],  a[r])
    };
    int m = l +(r - l) / 2;
    auto x = findMinMax(a,  l,  m),  y = findMinMax(a,  m + 1,  r);
    return {
        min(x.first,  y.first),  max(x.second,  y.second)
    };
}
int binarySearchIndex(const vector<long long> & a,  long long target) {
    int l = 0,  r =(int) a.size() - 1;
    while (l <= r) {
        int m = l +(r - l) / 2;
        if (a[m] == target) return m;
        if (a[m] < target) l = m + 1;
        else r = m - 1;
    }
    return - 1;
}
int main() {
    int n;
    cout << "Number of elements: ";
    if (!(cin >> n) || n <= 0) {
        cerr << "n must be positive.\n";
        return 1;
    }
    vector<long long> a(n);
    cout << "Enter elements: ";
    for (auto & x :  a) cin >> x;
    auto[mn,  mx] = findMinMax(a,  0,  n - 1);
    cout << "Minimum: " << mn << "\nMaximum: " << mx << "\n";
    sort(a.begin(),  a.end());
    cout << "Sorted array for binary search: ";
    for (auto x :  a) cout << x << ' ';
    cout << '\n';
    long long t;
    cout << "Target: ";
    cin >> t;
    int idx = binarySearchIndex(a,  t);
    if (idx < 0) cout << "Target not found.\n";
    else cout << "Target found at zero-based index " << idx << " in sorted array.\n";
}
