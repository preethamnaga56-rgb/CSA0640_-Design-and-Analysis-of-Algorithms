#include <bits/stdc++.h>
using namespace std;
using i128 = __int128_t;
i128 karatsuba(i128 x,  i128 y) {
    if (x < 10 || y < 10) return x * y;
    int n = max((int) to_string((long long) x).size(), (int) to_string((long long) y).size());
    int m = n / 2;
    i128 p = 1;
    for (int i = 0;  i < m; ++i) p *= 10;
    i128 a = x / p,  b = x % p,  c = y / p,  d = y % p;
    i128 z0 = karatsuba(b,  d),  z2 = karatsuba(a,  c),  z1 = karatsuba(a + b,  c + d) - z2 - z0;
    return z2 * p * p + z1 * p + z0;
}
string show(i128 x) {
    if (x == 0) return "0";
    string s;
    while (x) {
        s.push_back('0' + x % 10);
        x /= 10;
    }
    reverse(s.begin(),  s.end());
    return s;
}
int main() {
    long long x,  y;
    cout << "Enter two non-negative integers (up to 18 digits each): ";
    if (!(cin >> x >> y) || x < 0 || y < 0) {
        cerr << "Inputs must be non-negative integers.\n";
        return 1;
    }
    cout << "Product: " << show(karatsuba(x,  y)) << '\n';
}
