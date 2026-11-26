#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,  W;
    cout << "Number of items and integer capacity: ";
    if (!(cin >> n >> W) || n < 0 || W < 0 || W > 100000) {
        cerr << "Invalid input/capacity.\n";
        return 1;
    }
    vector<int> w(n),  v(n);
    for (int i = 0;  i < n;  i++) {
        cout << "Weight and value for item " << i + 1 << ": ";
        cin >> w[i] >> v[i];
        if (w[i] < 0 || v[i] < 0) {
            cerr << "Weights and values must be non-negative.\n";
            return 1;
        }
    }
    vector<vector<long long >> dp(n + 1,  vector<long long>(W + 1));
    for (int i = 1;  i <= n;  i++) for (int c = 0;  c <= W;  c++) {
        dp[i][c] = dp[i - 1][c];
        if (w[i - 1] <= c) dp[i][c] = max(dp[i][c],  dp[i - 1][c - w[i - 1]] + v[i - 1]);
    }
    cout << "Maximum value: " << dp[n][W] << "\nSelected item indices (1-based): ";
    int c = W;
    vector<int> chosen;
    for (int i = n;  i >= 1;  i--) if (dp[i][c] != dp[i - 1][c]) {
        chosen.push_back(i);
        c -= w[i - 1];
    }
    reverse(chosen.begin(),  chosen.end());
    for (int i :  chosen) cout << i << ' ';
    cout << '\n';
}
