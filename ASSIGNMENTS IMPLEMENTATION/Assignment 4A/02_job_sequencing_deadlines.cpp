#include <bits/stdc++.h>
using namespace std;
struct Job {
    string id;
    int deadline;
    long long profit;
};
int main() {
    int n;
    cout << "Number of jobs: ";
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid count.\n";
        return 1;
    }
    vector<Job> jobs(n);
    int D = 0;
    for (auto & j :  jobs) {
        cout << "Job ID deadline profit: ";
        cin >> j.id >> j.deadline >> j.profit;
        if (j.deadline < 0) {
            cerr << "Deadline cannot be negative.\n";
            return 1;
        }
        D = max(D,  j.deadline);
    }
    sort(jobs.begin(),  jobs.end(), [](auto & a,  auto & b) {
        return a.profit > b.profit;
    });
    vector<string> slot(min(D,  n) + 1);
    long long total = 0;
    for (auto & j :  jobs) for (int s = min({
        j.deadline,  D,  n
    });  s >= 1;  s--) if (slot[s].empty() && j.profit > 0) {
        slot[s] = j.id;
        total += j.profit;
        break;
    }
    for (int s = 1;  s <(int) slot.size();  s++) cout << "Slot " << s << ": " <<(slot[s].empty() ? "empty" :  slot[s]) << '\n';
    cout << "Total profit: " << total << '\n';
}
