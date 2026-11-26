#include <bits/stdc++.h>
using namespace std;
long long comparisons = 0;
int maxDepth = 0;
void mergeSort(vector<int> & a,  int l,  int r) {
    if (l >= r) return;
    int m = l +(r - l) / 2;
    mergeSort(a,  l,  m);
    mergeSort(a,  m + 1,  r);
    vector<int> t;
    int i = l,  j = m + 1;
    while (i <= m && j <= r) {
        ++comparisons;
        if (a[i] <= a[j]) t.push_back(a[i++]);
        else t.push_back(a[j++]);
    }
    while (i <= m) t.push_back(a[i++]);
    while (j <= r) t.push_back(a[j++]);
    copy(t.begin(),  t.end(),  a.begin() + l);
}
int partitionLast(vector<int> & a,  int l,  int r) {
    int pivot = a[r],  i = l - 1;
    for (int j = l;  j < r; ++j) {
        ++comparisons;
        if (a[j] <= pivot) swap(a[++i],  a[j]);
    }
    swap(a[i + 1],  a[r]);
    return i + 1;
}
void quickSort(vector<int> & a,  int l,  int r,  int depth = 1) {
    if (l >= r) return;
    maxDepth = max(maxDepth,  depth);
    int p = partitionLast(a,  l,  r);
    quickSort(a,  l,  p - 1,  depth + 1);
    quickSort(a,  p + 1,  r,  depth + 1);
}
void print(const vector<int> & a) {
    for (int x :  a) cout << x << ' ';
    cout << '\n';
}
int main() {
    int n;
    cout << "Number of elements: ";
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid size.\n";
        return 1;
    }
    vector<int> a(n);
    cout << "Enter elements: ";
    for (int & x :  a) cin >> x;
    auto b = a;
    comparisons = 0;
    mergeSort(a,  0,  n - 1);
    cout << "Merge sort: ";
    print(a);
    cout << "Merge comparisons: " << comparisons << '\n';
    comparisons = 0;
    maxDepth = 0;
    quickSort(b,  0,  n - 1);
    cout << "Quick sort (last-element pivot): ";
    print(b);
    cout << "Quick-sort comparisons: " << comparisons << "\nMaximum recursion depth: " << maxDepth << '\n';
}
