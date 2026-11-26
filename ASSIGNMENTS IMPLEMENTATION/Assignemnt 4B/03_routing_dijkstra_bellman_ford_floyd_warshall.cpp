#include <bits/stdc++.h>
using namespace std;
const long long INF =(1LL << 60);
struct E {
    int u,  v;
    long long w;
};
int main() {
    int n,  m;
    cout << "Vertices and directed edges: ";
    if (!(cin >> n >> m) || n <= 0 || m < 0 || n > 500) {
        cerr << "Invalid graph size.\n";
        return 1;
    }
    vector<E> e;
    vector<vector<pair<int,  long long >>> g(n);
    vector<vector<int >> reach(n,  vector<int>(n));
    bool negative = false;
    vector<vector<long long >> d(n,  vector<long long>(n,  INF));
    for (int i = 0;  i < n;  i++) d[i][i] = 0;
    for (int i = 0;  i < m;  i++) {
        E x;
        cout << "u v weight (0-based): ";
        cin >> x.u >> x.v >> x.w;
        if (x.u < 0 || x.u >= n || x.v < 0 || x.v >= n) {
            cerr << "Invalid vertex.\n";
            return 1;
        }
        e.push_back(x);
        g[x.u].push_back({
            x.v,  x.w
        });
        d[x.u][x.v] = min(d[x.u][x.v],  x.w);
        reach[x.u][x.v] = 1;
        negative |= x.w < 0;
    }
    int s;
    cout << "Source vertex: ";
    cin >> s;
    if (s < 0 || s >= n) {
        cerr << "Invalid source.\n";
        return 1;
    }
    if (!negative) {
        vector<long long> dist(n,  INF);
        dist[s] = 0;
        priority_queue<pair<long long,  int >,  vector<pair<long long,  int>>,  greater<>> pq;
        pq.push({
            0,  s
        });
        while (!pq.empty()) {
            auto[du,  u] = pq.top();
            pq.pop();
            if (du != dist[u]) continue;
            for (auto[v,  w] :  g[u]) if (dist[v] > du + w) {
                dist[v] = du + w;
                pq.push({
                    dist[v],  v
                });
            }
        }
        cout << "Dijkstra distances:\n";
        for (int i = 0;  i < n;  i++) cout << i << ": " <<(dist[i] == INF ? string("INF") :  to_string(dist[i])) << '\n';
    } else {
        vector<long long> dist(n,  INF);
        dist[s] = 0;
        for (int i = 1;  i < n;  i++) {
            bool ch = false;
            for (auto x :  e) if (dist[x.u] != INF && dist[x.v] > dist[x.u] + x.w) {
                dist[x.v] = dist[x.u] + x.w;
                ch = true;
            }
            if (!ch) break;
        }
        bool cycle = false;
        for (auto x :  e) if (dist[x.u] != INF && dist[x.v] > dist[x.u] + x.w) cycle = true;
        cout << "Bellman-Ford distances:\n";
        for (int i = 0;  i < n;  i++) cout << i << ": " <<(dist[i] == INF ? string("INF") :  to_string(dist[i])) << '\n';
        if (cycle) cout << "Reachable negative cycle detected.\n";
    }
    for (int k = 0;  k < n;  k++) for (int i = 0;  i < n;  i++) for (int j = 0;  j < n;  j++) reach[i][j] = reach[i][j] ||(reach[i][k] && reach[k][j]);
    cout << "Warshall reachability matrix (1=reachable):\n";
    for (auto & r :  reach) {
        for (int x :  r) cout << x << ' ';
        cout << '\n';
    }
    for (int k = 0;  k < n;  k++) for (int i = 0;  i < n;  i++) for (int j = 0;  j < n;  j++) if (d[i][k] != INF && d[k][j] != INF) d[i][j] = min(d[i][j],  d[i][k] + d[k][j]);
    cout << "Floyd-Warshall all-pairs matrix (INF=unreachable):\n";
    for (auto & r :  d) {
        for (auto x :  r) if (x == INF) cout << "INF ";
        else cout << x << ' ';
        cout << '\n';
    }
}
