#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
vector<int> ans = {5001, 5001, 1};

void processOrientation(bool isHorizontal) {
    int outer = isHorizontal ? m : n;  
    int inner = isHorizontal ? n : m;  
    vector<vector<pair<int,int>>> dp(outer);
    
    for (int o = 0; o < outer; o++) {
        bool flag = false;
        int startIndex = 0;
        for (int in = 0; in < inner; in++) {
            char cell = isHorizontal ? grid[o][in] : grid[in][o];
            if (!flag && cell == '0') {
                flag = true;
                startIndex = in;
            }
            if (flag && (cell == '1' || in == inner - 1)) {
                int endIndex;
                if (cell == '1')
                    endIndex = in - 1;
                else
                    endIndex = in;
                dp[o].push_back({startIndex, endIndex});
                flag = false;
            }
        }
    }

    for (int o = 0; o < outer - 1; o++) {
        int i = 0, j = 0;
        while (i < dp[o].size() && j < dp[o+1].size()) {
            int segStart = max(dp[o][i].first, dp[o+1][j].first);
            int segEnd = min(dp[o][i].second, dp[o+1][j].second);
            if (segStart <= segEnd) {
                int length = segEnd - segStart + 1;
                if (length > ans[2]) {
                    if (isHorizontal) {
                        ans[0] = segStart;
                        ans[1] = o;
                    } else {
                        ans[0] = o;
                        ans[1] = segStart;
                    }
                    ans[2] = length;
                }
            }
            if (dp[o][i].second < dp[o+1][j].second)
                i++;
            else
                j++;
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    
    cin >> m >> n;
    for (int j = 0; j < m; j++) {
        string s; cin >> s;
        grid.push_back(s);
    }
    
    processOrientation(true);   
    processOrientation(false);  
    if (ans[2] < 2) cout << "0 0 0\n";
    else cout << ans[0] + 1 << " " << m - ans[1] << " " << ans[2] << "\n";
    
    return 0;
}
