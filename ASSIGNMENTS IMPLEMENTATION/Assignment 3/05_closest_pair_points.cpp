#include <bits/stdc++.h>
using namespace std;
struct Point {
    long long x,  y;
};
long double dist2(const Point & a,  const Point & b) {
    long double dx =(long double) a.x - b.x,  dy =(long double) a.y - b.y;
    return dx * dx + dy * dy;
}
long double solve(vector<Point> & p,  int l,  int r) {
    if (r - l <= 3) {
        long double best = numeric_limits<long double>::infinity();
        for (int i = l;  i < r;  i++) for (int j = i + 1;  j < r;  j++) best = min(best,  dist2(p[i],  p[j]));
        sort(p.begin() + l,  p.begin() + r, [](auto & a,  auto & b) {
            return a.y < b.y;
        });
        return best;
    }
    int m = l +(r - l) / 2;
    long long midx = p[m].x;
    auto dl = solve(p,  l,  m),  dr = solve(p,  m,  r);
    long double best = min(dl,  dr);
    vector<Point> strip;
    for (int i = l;  i < r;  i++) {
        long double dx =(long double) p[i].x - midx;
        if (dx * dx < best) strip.push_back(p[i]);
    }
    sort(strip.begin(),  strip.end(), [](auto & a,  auto & b) {
        return a.y < b.y;
    });
    for (int i = 0;  i <(int) strip.size();  i++) for (int j = i + 1;  j <(int) strip.size();  j++) {
        long double dy =(long double) strip[j].y - strip[i].y;
        if (dy * dy >= best) break;
        best = min(best,  dist2(strip[i],  strip[j]));
    }
    return best;
}
int main() {
    int n;
    cout << "Number of points (at least 2): ";
    if (!(cin >> n) || n < 2) {
        cerr << "At least two points are required.\n";
        return 1;
    }
    vector<Point> p(n);
    cout << "Enter x y for each point:\n";
    for (auto & q :  p) cin >> q.x >> q.y;
    sort(p.begin(),  p.end(), [](auto & a,  auto & b) {
        return a.x < b.x ||(a.x == b.x && a.y < b.y);
    });
    cout << fixed << setprecision(6) << "Closest distance: " << sqrt(solve(p,  0,  n)) << '\n';
}
