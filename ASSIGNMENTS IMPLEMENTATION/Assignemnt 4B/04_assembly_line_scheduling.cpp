#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cout << "Stations per line: ";
    if (!(cin >> n) || n <= 0 || n > 100000) {
        cerr << "Invalid station count.\n";
        return 1;
    }
    vector<long long> a[2],  t[2];
    for (int l = 0;  l < 2;  l++) {
        a[l].resize(n);
        cout << "Processing times for line " << l + 1 << ": ";
        for (auto & x :  a[l]) cin >> x;
    }
    for (int l = 0;  l < 2;  l++) {
        t[l].resize(max(0,  n - 1));
        cout << "Transfer times from line " << l + 1 << " to the other line (" << n - 1 << " values): ";
        for (auto & x :  t[l]) cin >> x;
    }
    long long e1,  e2,  x1,  x2;
    cout << "Entry times line1 line2: ";
    cin >> e1 >> e2;
    cout << "Exit times line1 line2: ";
    cin >> x1 >> x2;
    vector<long long> f1(n),  f2(n);
    vector<int> p1(n),  p2(n);
    f1[0] = e1 + a[0][0];
    f2[0] = e2 + a[1][0];
    for (int i = 1;  i < n;  i++) {
        if (f1[i - 1] + a[0][i] <= f2[i - 1] + t[1][i - 1] + a[0][i]) {
            f1[i] = f1[i - 1] + a[0][i];
            p1[i] = 0;
        } else {
            f1[i] = f2[i - 1] + t[1][i - 1] + a[0][i];
            p1[i] = 1;
        }
        if (f2[i - 1] + a[1][i] <= f1[i - 1] + t[0][i - 1] + a[1][i]) {
            f2[i] = f2[i - 1] + a[1][i];
            p2[i] = 1;
        } else {
            f2[i] = f1[i - 1] + t[0][i - 1] + a[1][i];
            p2[i] = 0;
        }
    }
    int line;
    long long best;
    if (f1[n - 1] + x1 <= f2[n - 1] + x2) {
        best = f1[n - 1] + x1;
        line = 0;
    } else {
        best = f2[n - 1] + x2;
        line = 1;
    }
    vector<int> path(n);
    for (int i = n - 1;  i >= 0;  i--) {
        path[i] = line;
        if (i > 0) line =(line == 0 ? p1[i] :  p2[i]);
    }
    cout << "Minimum total time: " << best << "\nLine choices by station: ";
    for (int q :  path) cout << q + 1 << ' ';
    cout << '\n';
}
