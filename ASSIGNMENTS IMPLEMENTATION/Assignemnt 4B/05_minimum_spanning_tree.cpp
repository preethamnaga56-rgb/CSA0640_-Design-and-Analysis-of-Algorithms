#include <bits/stdc++.h>
using namespace std;
struct E {
    int u,  v;
    long long w;
};
struct DSU {
    vector<int> p,  r;
    DSU(int n) :  p(n),  r(n) {
        iota(p.begin(),  p.end(),  0);
    }
    int find(int x) {
        return p[x] == x ? x :  p[x] = find(p[x]);
    }
    bool join(int a,  int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,  b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};
int main() {
    int n,  m;
    cout << "Vertices and undirected edges: ";
    if (!(cin >> n >> m) || n <= 0 || m < 0) {
        cerr << "Invalid graph.\n";
        return 1;
    }
    vector<E> e(m);
    vector<vector<pair<int,  long long >>> g(n);
    for (auto & x :  e) {
        cout << "u v weight (0-based): ";
        cin >> x.u >> x.v >> x.w;
        if (x.u < 0 || x.u >= n || x.v < 0 || x.v >= n) {
            cerr << "Invalid vertex.\n";
            return 1;
        }
        g[x.u].push_back({
            x.v,  x.w
        });
        g[x.v].push_back({
            x.u,  x.w
        });
    }
    auto sorted = e;
    sort(sorted.begin(),  sorted.end(), [](auto & a,  auto & b) {
        return a.w < b.w;
    });
    DSU dsu(n);
    long long kw = 0;
    vector<E> ke;
    for (auto x :  sorted) if (dsu.join(x.u,  x.v)) {
        ke.push_back(x);
        kw += x.w;
    }
    cout << "Kruskal: ";
    if ((int) ke.size() != n - 1) cout << "graph disconnected; minimum spanning forest weight=" << kw << '\n';
    else cout << "weight=" << kw << '\n';
    for (auto x :  ke) cout << x.u << " - " << x.v << " : " << x.w << '\n';
    vector<char> used(n);
    long long pw = 0;
    int cnt = 0;
    priority_queue<tuple<long long,  int,  int >,  vector<tuple<long long,  int,  int>>,  greater<>> pq;
    pq.push({
        0,  0,  - 1
    });
    while (!pq.empty()) {
        auto[w,  u,  par] = pq.top();
        pq.pop();
        if (used[u]) continue;
        used[u] = 1;
        pw += w;
        if (par != - 1) cnt++;
        for (auto[v,  c] :  g[u]) if (!used[v]) pq.push({
            c,  v,  u
        });
    }
    cout << "Prim from vertex 0: ";
    if (cnt != n - 1) cout << "graph disconnected; forest weight=" << pw << '\n';
    else cout << "weight=" << pw << '\n';
}
