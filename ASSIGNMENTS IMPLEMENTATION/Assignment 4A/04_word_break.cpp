#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    int n;
    cout << "Text (no spaces): ";
    cin >> s;
    cout << "Dictionary word count: ";
    if (!(cin >> n) || n < 0) {
        cerr << "Invalid count.\n";
        return 1;
    }
    unordered_set<string> dict;
    cout << "Enter dictionary words:\n";
    for (int i = 0;  i < n;  i++) {
        string w;
        cin >> w;
        dict.insert(w);
    }
    int m = s.size();
    vector<char> dp(m + 1,  false);
    vector<int> prev(m + 1,  - 1);
    dp[0] = true;
    for (int i = 1;  i <= m;  i++) for (int j = 0;  j < i;  j++) if (dp[j] && dict.count(s.substr(j,  i - j))) {
        dp[i] = true;
        prev[i] = j;
        break;
    }
    if (!dp[m]) {
        cout << "Cannot segment text using the dictionary.\n";
        return 0;
    }
    vector<string> parts;
    for (int i = m;  i > 0;  i = prev[i]) parts.push_back(s.substr(prev[i],  i - prev[i]));
    reverse(parts.begin(),  parts.end());
    cout << "Segmentable: yes\nSegmentation: ";
    for (auto & w :  parts) cout << w << ' ';
    cout << '\n';
}
