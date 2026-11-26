#include <bits/stdc++.h>
using namespace std;
const long long INF =(1LL << 60);
int main() {
    int n;
    cout << "Number of cities (1..20): ";
    if (!(cin >> n) || n < 1 || n > 20) {
        cerr << "n must be between 1 and 20.\n";
        return 1;
    }
    vector<vector<long long >> w(n,  vector<long long>(n));
    cout << "Enter cost matrix (use -1 for no edge):\n";
    for (int i = 0;  i < n;  i++) for (int j = 0;  j < n;  j++) {
        cin >> w[i][j];
        if (i != j && w[i][j] < 0) w[i][j] = INF;
    }
    if (n == 1) {
        cout << "Minimum tour cost: 0\nTour: 0 0\n";
        return 0;
    }
    size_t N = 1u << n;
    vector<vector<long long >> dp(N,  vector<long long>(n,  INF));
    vector<vector<int >> par(N,  vector<int>(n,  - 1));
    dp[1][0] = 0;
    for (size_t mask = 1;  mask < N;  mask++) {
        if (!(mask & 1)) continue;
        for (int u = 0;  u < n;  u++) if (dp[mask][u] != INF) for (int v = 0;  v < n;  v++) if (!(mask &(1u << v)) && w[u][v] != INF) {
            size_t nm = mask |(1u << v);
            long long cand = dp[mask][u] + w[u][v];
            if (cand < dp[nm][v]) {
                dp[nm][v] = cand;
                par[nm][v] = u;
            }
        }
    }
    size_t full = N - 1;
    long long best = INF;
    int last = - 1;
    for (int u = 1;  u < n;  u++) if (dp[full][u] != INF && w[u][0] != INF && dp[full][u] + w[u][0] < best) {
        best = dp[full][u] + w[u][0];
        last = u;
    }
    if (last < 0) {
        cout << "No Hamiltonian tour exists.\n";
        return 0;
    }
    vector<int> path;
    size_t mask = full;
    int cur = last;
    while (cur != 0) {
        path.push_back(cur);
        int prev = par[mask][cur];
        mask ^= 1u << cur;
        cur = prev;
    }
    path.push_back(0);
    reverse(path.begin(),  path.end());
    path.push_back(0);
    cout << "Minimum tour cost: " << best << "\nTour: ";
    for (int x :  path) cout << x << ' ';
    cout << '\n';
}
