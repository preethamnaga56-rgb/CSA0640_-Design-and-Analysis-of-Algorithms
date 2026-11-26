#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,  W;
    cout << "Number of words and line width: ";
    if (!(cin >> n >> W) || n < 0 || W <= 0) {
        cerr << "Invalid input.\n";
        return 1;
    }
    vector<string> w(n);
    cout << "Enter words:\n";
    for (auto & s :  w) {
        cin >> s;
        if ((int) s.size() > W) {
            cerr << "Word '" << s << "' exceeds line width.\n";
            return 1;
        }
    }
    const long long INF =(1LL << 60);
    vector<long long> dp(n + 1,  INF);
    vector<int> next(n,  - 1),  usedAt(n);
    dp[n] = 0;
    for (int i = n - 1;  i >= 0;  i--) {
        int used = 0;
        for (int j = i;  j < n;  j++) {
            used +=(int) w[j].size() +(j > i);
            if (used > W) break;
            long long extra = W - used,  line =(j == n - 1 ? 0 :  extra * extra);
            if (dp[j + 1] != INF && line + dp[j + 1] < dp[i]) {
                dp[i] = line + dp[j + 1];
                next[i] = j + 1;
                usedAt[i] = used;
            }
        }
    }
    if (dp[0] == INF) {
        cout << "No feasible layout.\n";
        return 0;
    }
    cout << "Minimum penalty: " << dp[0] << '\n';
    for (int i = 0;  i < n; ) {
        int j = next[i];
        for (int k = i;  k < j;  k++) {
            if (k > i) cout << ' ';
            cout << w[k];
        }
        cout << " | used=" << usedAt[i] << ", unused=" << W - usedAt[i] << ", penalty=" <<(j == n ? 0LL :  1LL *(W - usedAt[i]) *(W - usedAt[i])) << '\n';
        i = j;
    }
}
