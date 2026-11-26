#include <bits/stdc++.h>
using namespace std;
struct Item {
    string id;
    double weight,  value;
};
int main() {
    int n;
    double cap;
    cout << "Number of items and capacity: ";
    if (!(cin >> n >> cap) || n < 0 || cap < 0) {
        cerr << "Invalid input.\n";
        return 1;
    }
    vector<Item> a(n);
    for (int i = 0;  i < n;  i++) {
        cout << "Item ID, weight, value: ";
        cin >> a[i].id >> a[i].weight >> a[i].value;
        if (a[i].weight <= 0 || a[i].value < 0) {
            cerr << "Weights must be positive and values non-negative.\n";
            return 1;
        }
    }
    sort(a.begin(),  a.end(), [](auto & x,  auto & y) {
        return x.value / x.weight > y.value / y.weight;
    });
    double rem = cap,  total = 0;
    cout << fixed << setprecision(3);
    for (auto & i :  a) {
        if (rem <= 1e-9) break;
        double f = min(1.0,  rem / i.weight);
        if (f > 0) {
            cout << i.id << ": fraction=" << f << ", weight=" << f * i.weight << ", value=" << f * i.value << '\n';
            rem -= f * i.weight;
            total += f * i.value;
        }
    }
    cout << "Loaded weight: " << cap - rem << "\nTotal value: " << total << '\n';
}
