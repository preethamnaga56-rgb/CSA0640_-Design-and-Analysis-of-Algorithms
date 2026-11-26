#include <bits/stdc++.h>
using namespace std;
struct Job {
    int start,  finish;
    long long profit;
};
int main() {
    int n;
    cout << "Number of jobs: ";
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid count.\n";
        return 1;
    }
    vector<Job> a(n);
    for (auto & j :  a) {
        cout << "Start finish profit: ";
        cin >> j.start >> j.finish >> j.profit;
        if (j.finish < j.start) {
            cerr << "Finish must be >= start.\n";
            return 1;
        }
    }
    sort(a.begin(),  a.end(), [](auto & x,  auto & y) {
        return x.finish < y.finish;
    });
    vector<int> ends(n);
    for (int i = 0;  i < n;  i++) ends[i] = a[i].finish;
    vector<int> p(n);
    for (int i = 0;  i < n;  i++) p[i] = int(lower_bound(ends.begin(),  ends.begin() + i,  a[i].start) - ends.begin()) - 1;
    vector<long long> dp(n + 1);
    for (int i = 1;  i <= n;  i++) dp[i] = max(dp[i - 1],  a[i - 1].profit + dp[p[i - 1] + 1]);
    cout << "Maximum profit: " << dp[n] << "\nSelected jobs (start finish profit):\n";
    vector<Job> chosen;
    for (int i = n;  i > 0; ) {
        if (a[i - 1].profit + dp[p[i - 1] + 1] > dp[i - 1]) {
            chosen.push_back(a[i - 1]);
            i = p[i - 1] + 1;
        } else--i;
    }
    reverse(chosen.begin(),  chosen.end());
    for (auto j :  chosen) cout << j.start << ' ' << j.finish << ' ' << j.profit << '\n';
}
