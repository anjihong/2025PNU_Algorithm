#include <bits/stdc++.h>

using namespace std;
int n,m;
vector<string> grid;
vector<int> ans = {5001,5001,1};

void horizontal() {
    int length = 0;
    for (int j = 0; j < n-1; j++) {
        for (int i = 0; i < m; i++) {
            if (!((grid[j][i]-'0')|(grid[j+1][i]-'0'))) {
                length++;
            }
            else {
                if ((length > ans[2])||((length == ans[2]) && (ans[0] > i-length))) {
                    ans[0] = i-length;
                    ans[1] = j+1;
                    ans[2] = length;
                }
                length = 0;
            }
        }
        if ((length > ans[2])||((length == ans[2]) && (ans[0] > m-length))) {
            ans[0] = m-length;
            ans[1] = j+1;
            ans[2] = length;
        }
        length = 0;
    }
}

void vertical() {
    int length = 0;
    for (int i = 0; i < m-1; i++) {
        for (int j = 0; j < n; j++) {
            if (!((grid[j][i]-'0')|(grid[j][i+1]-'0'))) {
                length++;
            }
            else {
                if (length > ans[2]) {
                    ans[0] = i;
                    ans[1] = j-1;
                    ans[2] = length;
                }

                else if (length == ans[2]) {
                    if ((ans[0] > i) || ((ans[0] == i && ans[1] > j-1))) {
                        ans[0] = i;
                        ans[1] = j-1;
                        ans[2] = length;
                    }
                }
                length = 0;
            }
        }
        if (length > ans[2]) {
            ans[0] = i;
            ans[1] = n-1;
            ans[2] = length;
        }
        else if (length == ans[2]) {
            if ((ans[0] > i) || ((ans[0] == i && ans[1] > n-length))) {
                ans[0] = i;
                ans[1] = n-1;
                ans[2] = length;
            }
        }
        length = 0;
    }
}


int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for (int j = 0; j < n; j++) {
        string s; cin >> s;
        grid.insert(grid.begin(), s);
    }



    horizontal();
    vertical();
    if (ans[2] < 2){
        cout << "0 0 0\n";
        return 0;  
    } 
    cout << ans[0]+1 << " " << ans[1]+1 << " " << ans[2] << "\n";
}