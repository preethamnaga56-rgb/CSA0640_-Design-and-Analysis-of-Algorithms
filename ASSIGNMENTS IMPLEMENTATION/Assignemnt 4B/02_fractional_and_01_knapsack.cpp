#include <bits/stdc++.h>
using namespace std;
struct Item {
    string id;
    int weight;
    long long value;
};
int main() {
    int n,  W;
    cout << "Item count and capacity: ";
    if (!(cin >> n >> W) || n < 0 || W < 0 || W > 100000) {
        cerr << "Invalid input.\n";
        return 1;
    }
    vector<Item> a(n);
    for (auto & i :  a) {
        cout << "ID weight value: ";
        cin >> i.id >> i.weight >> i.value;
        if (i.weight <= 0 || i.value < 0) {
            cerr << "Weight must be positive; value non-negative.\n";
            return 1;
        }
    }
    auto sorted = a;
    sort(sorted.begin(),  sorted.end(), [](auto & x,  auto & y) {
        return(long double) x.value / x.weight >(long double) y.value / y.weight;
    });
    double rem = W,  fracVal = 0;
    cout << fixed << setprecision(3) << "Fractional selection:\n";
    for (auto & i :  sorted) {
        if (rem <= 0) break;
        double f = min(1.0,  rem / i.weight);
        if (f > 0) {
            cout << i.id << " fraction=" << f << '\n';
            fracVal += f * i.value;
            rem -= f * i.weight;
        }
    }
    cout << "Fractional maximum value: " << fracVal << '\n';
    vector<vector<long long >> dp(n + 1,  vector<long long>(W + 1));
    for (int i = 1;  i <= n;  i++) for (int c = 0;  c <= W;  c++) {
        dp[i][c] = dp[i - 1][c];
        if (a[i - 1].weight <= c) dp[i][c] = max(dp[i][c],  dp[i - 1][c - a[i - 1].weight] + a[i - 1].value);
    }
    cout << "0/1 maximum value: " << dp[n][W] << "\nSelected 0/1 items: ";
    int c = W;
    vector<string> sel;
    for (int i = n;  i > 0;  i--) if (dp[i][c] != dp[i - 1][c]) {
        sel.push_back(a[i - 1].id);
        c -= a[i - 1].weight;
    }
    reverse(sel.begin(),  sel.end());
    for (auto & s :  sel) cout << s << ' ';
    cout << '\n';
}
