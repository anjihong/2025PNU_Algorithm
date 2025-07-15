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
        pair<int,int> seg = {0, 0};
        for (int in = 0; in < inner; in++) {
            char cell = isHorizontal ? grid[o][in] : grid[in][o];
            if (!flag && cell == '0') {
                flag = true;
                seg.first = in;
            } else if (flag && (cell == '1' || in == inner - 1)) {
                if (seg.first == in) {
                    flag = false;
                    continue;
                }

                if (in == inner - 1 && cell == '0')
                    seg.second = in;
                else
                    seg.second = in - 1;
                dp[o].push_back(seg);
                flag = false;
            }
        }
    }
    
    for (int o = 0; o < outer - 1; o++) {
        for (auto seg1 : dp[o]) {
            for (auto seg2 : dp[o+1]) {
                int segStart = max(seg1.first, seg2.first);
                int segEnd = min(seg1.second, seg2.second);
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
            }
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
