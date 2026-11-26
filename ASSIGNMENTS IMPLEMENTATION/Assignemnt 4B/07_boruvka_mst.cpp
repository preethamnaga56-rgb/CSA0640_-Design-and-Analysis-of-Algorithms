#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int u,  v;
    long long w;
};
struct DSU {
    vector<int> p,  rankv;
    DSU(int n) :  p(n),  rankv(n) {
        iota(p.begin(),  p.end(),  0);
    }
    int find(int x) {
        return p[x] == x ? x :  p[x] = find(p[x]);
    }
    bool unite(int a,  int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (rankv[a] < rankv[b]) swap(a,  b);
        p[b] = a;
        if (rankv[a] == rankv[b]) rankv[a]++;
        return true;
    }
};
int main() {
    int n,  m;
    cout << "Vertices and edges: ";
    if (!(cin >> n >> m) || n <= 0 || m < 0) {
        cerr << "Invalid graph size.\\n";
        return 1;
    }
    vector<Edge> edges(m);
    for (auto & e :  edges) {
        cout << "u v weight (0-based): ";
        cin >> e.u >> e.v >> e.w;
        if (e.u < 0 || e.u >= n || e.v < 0 || e.v >= n) {
            cerr << "Invalid vertex.\\n";
            return 1;
        }
    }
    DSU dsu(n);
    int components = n;
    long long total = 0;
    vector<Edge> chosen;
    while (components > 1) {
        vector<int> cheapest(n,  - 1);
        for (int i = 0;  i < m;  i++) {
            int a = dsu.find(edges[i].u),  b = dsu.find(edges[i].v);
            if (a == b) continue;
            if (cheapest[a] == - 1 || edges[i].w < edges[cheapest[a]].w) cheapest[a] = i;
            if (cheapest[b] == - 1 || edges[i].w < edges[cheapest[b]].w) cheapest[b] = i;
        }
        bool merged = false;
        for (int idx :  cheapest) if (idx != - 1) {
            auto e = edges[idx];
            if (dsu.unite(e.u,  e.v)) {
                chosen.push_back(e);
                total += e.w;
                components--;
                merged = true;
            }
        }
        if (!merged) break;
    }
    if (components > 1) cout << "Graph is disconnected; minimum spanning forest weight: ";
    else cout << "MST weight: ";
    cout << total << "\\nEdges selected:\\n";
    for (auto e :  chosen) cout << e.u << " - " << e.v << " : " << e.w << "\\n";
}
