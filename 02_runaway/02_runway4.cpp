#include <bits/stdc++.h>

using namespace std;
int n, m;
vector<string> grid;
vector<int> ans = {5001, 5001, 1};


void horizontal() {
    vector<vector<pair<int,int>>> dp;
    for (int j = 0; j < m; j++) {
        vector<pair<int,int>> temp;
        bool flag = 0;
        pair<int,int> p = {0,0};
        for (int i = 0; i < n; i++) {
            if(!flag && grid[j][i] == '0') {
                flag = 1;
                p.first = i;
            }
            else if(((grid[j][i] == '1' || i == n-1) && flag)) {
                if (i == n-1) p.second = i;
                else p.second = i-1;
                temp.push_back(p);
                flag = 0;
            }
        }
        dp.push_back(temp);
    }

    for (int j = 0; j < m-1; j++) {
        for (int i = 0; i < dp[j].size(); i++) {
            for (int k = 0; k < dp[j+1].size(); k++) {
                int start = max(dp[j][i].first, dp[j+1][k].first);
                int end = min(dp[j][i].second, dp[j+1][k].second);
                if (start <= end) {
                    if (end - start + 1 > ans[2]) {
                        ans[0] = start;
                        ans[1] = j;
                        ans[2] = end - start + 1;
                    }
                }
            }
        }
    }
}

void vertical() {
    vector<vector<pair<int,int>>> dp;
    for (int i = 0; i < n; i++) {
        vector<pair<int,int>> temp;
        bool flag = 0;
        pair<int,int> p = {0,0};
        for (int j = 0; j < m; j++) {
            if(!flag && grid[j][i] == '0') {
                flag = 1;
                p.first = j;
            }
            else if((grid[j][i] == '1' || j == m-1) && flag) {
                if (j == m-1) p.second = j;
                else p.second = j-1;
                temp.push_back(p);
                flag = 0;
            }
        }
        dp.push_back(temp);
    }

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < dp[i].size(); j++) {
            for (int k = 0; k < dp[i+1].size(); k++) {
                int start = max(dp[i][j].first, dp[i+1][k].first);
                int end = min(dp[i][j].second, dp[i+1][k].second);
                if (start <= end) {
                    if (end - start + 1 > ans[2]) {
                        ans[0] = i;
                        ans[1] = start;
                        ans[2] = end - start + 1;
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> m >> n;
    for (int j = 0; j < m; j++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    horizontal();
    vertical();

    if (ans[2] < 2){
        cout << "0 0 0\n";
    }
    else {
        cout << ans[0] + 1 << " " << m - ans[1] << " " << ans[2] << "\n";
    }

}