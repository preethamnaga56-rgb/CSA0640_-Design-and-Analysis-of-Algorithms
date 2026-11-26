#include <bits/stdc++.h>
using namespace std;
int selectK(vector<int> & a,  int k) {
    if (a.size() <= 5) {
        sort(a.begin(),  a.end());
        return a[k];
    }
    vector<int> med;
    for (int i = 0;  i <(int) a.size();  i += 5) {
        vector<int> g(a.begin() + i,  a.begin() + min((int) a.size(),  i + 5));
        sort(g.begin(),  g.end());
        med.push_back(g[g.size() / 2]);
    }
    int pivot = selectK(med,  med.size() / 2);
    vector<int> lo,  eq,  hi;
    for (int x :  a)(x < pivot ? lo :  x > pivot ? hi :  eq).push_back(x);
    if (k <(int) lo.size()) return selectK(lo,  k);
    if (k <(int)(lo.size() + eq.size())) return pivot;
    return selectK(hi,  k - lo.size() - eq.size());
}
int main() {
    int n;
    cout << "Number of values (1..40): ";
    if (!(cin >> n) || n < 1 || n > 40) {
        cerr << "n must be between 1 and 40.\n";
        return 1;
    }
    vector<int> a(n);
    cout << "Enter values: ";
    for (int & x :  a) cin >> x;
    int k;
    cout << "Enter 1-based rank k: ";
    cin >> k;
    if (k < 1 || k > n) {
        cerr << "Invalid rank.\n";
        return 1;
    }
    auto b = a;
    cout << k << "-th smallest (Median of Medians): " << selectK(b,  k - 1) << '\n';
    long long target;
    cout << "Subset-sum target: ";
    cin >> target;
    int mid = n / 2;
    auto makeSums =[&](int l,  int r) {
        vector<long long> v {
            0
        };
        for (int i = l;  i < r;  i++) {
            int old =(int) v.size();
            for (int j = 0;  j < old;  j++) v.push_back(v[j] + a[i]);
        }
        return v;
    };
    auto left = makeSums(0,  mid),  right = makeSums(mid,  n);
    sort(right.begin(),  right.end());
    bool found = false;
    for (long long x :  left) if (binary_search(right.begin(),  right.end(),  target - x)) {
        found = true;
        break;
    }
    cout << "Subset sum target " << target << ": " <<(found ? "reachable" :  "not reachable") << " (meet-in-the-middle)\n";
}
