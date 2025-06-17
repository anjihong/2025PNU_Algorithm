#include <bits/stdc++.h>

using namespace std;
int n;
vector<pair<char, int>> dq;
vector<char> mount;
vector<char> sea;
pair<char, int> p;
int cur = 0;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p.first >> p.second;
        dq.push_back(p);
    }

    for (auto p : dq) {
        if (p.second > cur) {
            mount.push_back(p.first);
            cur = p.second;
        }
    }
    
    cur = 0;

    for (auto it = dq.end() - 1; it >= dq.begin(); it--) {
        if (it->second > cur) {
            sea.insert(sea.begin(), it->first);
            cur = it->second;
        }
    }

    for (auto i : mount) cout << i << " ";
    cout << "\n";
    for (auto i : sea) cout << i << " ";



}