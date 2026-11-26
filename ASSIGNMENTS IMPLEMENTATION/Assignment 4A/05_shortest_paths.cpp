#include <bits/stdc++.h>
using namespace std;
const long long INF =(1LL << 60);
struct Edge {
    int u,  v;
    long long w;
};
int main() {
    int n,  m,  s;
    cout << "Vertices, edges, source (0-based): ";
    if (!(cin >> n >> m >> s) || n <= 0 || m < 0 || s < 0 || s >= n) {
        cerr << "Invalid graph.\n";
        return 1;
    }
    vector<Edge> e;
    vector<vector<pair<int,  long long >>> g(n);
    bool neg = false;
    for (int i = 0;  i < m;  i++) {
        Edge x;
        cout << "Directed edge u v weight: ";
        cin >> x.u >> x.v >> x.w;
        if (x.u < 0 || x.u >= n || x.v < 0 || x.v >= n) {
            cerr << "Invalid vertex.\n";
            return 1;
        }
        e.push_back(x);
        g[x.u].push_back({
            x.v,  x.w
        });
        neg |= x.w < 0;
    }
    vector<long long> d(n,  INF);
    d[s] = 0;
    if (!neg) {
        priority_queue<pair<long long,  int >,  vector<pair<long long,  int>>,  greater<>> pq;
        pq.push({
            0,  s
        });
        while (!pq.empty()) {
            auto[du,  u] = pq.top();
            pq.pop();
            if (du != d[u]) continue;
            for (auto[v,  w] :  g[u]) if (d[u] != INF && d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pq.push({
                    d[v],  v
                });
            }
        }
        cout << "Algorithm: Dijkstra\n";
    } else {
        for (int i = 1;  i < n;  i++) {
            bool changed = false;
            for (auto x :  e) if (d[x.u] != INF && d[x.v] > d[x.u] + x.w) {
                d[x.v] = d[x.u] + x.w;
                changed = true;
            }
            if (!changed) break;
        }
        for (auto x :  e) if (d[x.u] != INF && d[x.v] > d[x.u] + x.w) {
            cout << "Reachable negative-weight cycle detected.\n";
            return 0;
        }
        cout << "Algorithm: Bellman-Ford\n";
    }
    for (int i = 0;  i < n;  i++) cout << "Distance to " << i << ": " <<(d[i] == INF ? string("unreachable") :  to_string(d[i])) << '\n';
}
