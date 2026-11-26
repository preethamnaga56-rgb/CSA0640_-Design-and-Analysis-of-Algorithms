#include <bits/stdc++.h>
using namespace std;
using Matrix = vector<vector<long long>>;
Matrix add(const Matrix & a,  const Matrix & b,  int sign = 1) {
    int n = a.size();
    Matrix c(n,  vector<long long>(n));
    for (int i = 0;  i < n;  i++) for (int j = 0;  j < n;  j++) c[i][j] = a[i][j] + sign * b[i][j];
    return c;
}
Matrix conventional(const Matrix & a,  const Matrix & b) {
    int n = a.size();
    Matrix c(n,  vector<long long>(n));
    for (int i = 0;  i < n;  i++) for (int k = 0;  k < n;  k++) for (int j = 0;  j < n;  j++) c[i][j] += a[i][k] * b[k][j];
    return c;
}
Matrix strassen(const Matrix & a,  const Matrix & b) {
    int n = a.size();
    if (n <= 2) return conventional(a,  b);
    int h = n / 2;
    Matrix a11(h,  vector<long long>(h)),  a12 = a11,  a21 = a11,  a22 = a11,  b11 = a11,  b12 = a11,  b21 = a11,  b22 = a11;
    for (int i = 0;  i < h;  i++) for (int j = 0;  j < h;  j++) {
        a11[i][j] = a[i][j];
        a12[i][j] = a[i][j + h];
        a21[i][j] = a[i + h][j];
        a22[i][j] = a[i + h][j + h];
        b11[i][j] = b[i][j];
        b12[i][j] = b[i][j + h];
        b21[i][j] = b[i + h][j];
        b22[i][j] = b[i + h][j + h];
    }
    auto m1 = strassen(add(a11,  a22),  add(b11,  b22));
    auto m2 = strassen(add(a21,  a22),  b11);
    auto m3 = strassen(a11,  add(b12,  b22,  - 1));
    auto m4 = strassen(a22,  add(b21,  b11,  - 1));
    auto m5 = strassen(add(a11,  a12),  b22);
    auto m6 = strassen(add(a21,  a11,  - 1),  add(b11,  b12));
    auto m7 = strassen(add(a12,  a22,  - 1),  add(b21,  b22));
    auto c11 = add(add(add(m1,  m4),  m5,  - 1),  m7);
    auto c12 = add(m3,  m5);
    auto c21 = add(m2,  m4);
    auto c22 = add(add(add(m1,  m2,  - 1),  m3),  m6);
    Matrix c(n,  vector<long long>(n));
    for (int i = 0;  i < h;  i++) for (int j = 0;  j < h;  j++) {
        c[i][j] = c11[i][j];
        c[i][j + h] = c12[i][j];
        c[i + h][j] = c21[i][j];
        c[i + h][j + h] = c22[i][j];
    }
    return c;
}
int main() {
    int n;
    cout << "Matrix dimension n (1..64): ";
    if (!(cin >> n) || n < 1 || n > 64) {
        cerr << "Invalid dimension.\n";
        return 1;
    }
    int p = 1;
    while (p < n) p *= 2;
    Matrix a(p,  vector<long long>(p)),  b = a;
    cout << "Enter matrix A (n x n):\n";
    for (int i = 0;  i < n;  i++) for (int j = 0;  j < n;  j++) cin >> a[i][j];
    cout << "Enter matrix B (n x n):\n";
    for (int i = 0;  i < n;  i++) for (int j = 0;  j < n;  j++) cin >> b[i][j];
    auto c = strassen(a,  b);
    cout << "Product A x B:\n";
    for (int i = 0;  i < n;  i++) {
        for (int j = 0;  j < n;  j++) cout << c[i][j] << ' ';
        cout << '\n';
    }
}
