#include <bits/stdc++.h>
using namespace std;

int n;
vector<pair<int,int>> point;

int dist2(int i, int j) {
    double d = sqrt(pow(point[i].first - point[j].first, 2) + pow(point[i].second - point[j].second, 2));
    return int(d);
}

void solve() {
    vector<vector<int>> dp(n+1, vector<int>(n+1, INT_MAX)); 

    dp[0][1] = dist2(0,1);

    for(int j = 2; j <= n; ++j){
        for(int i = 0; i < j-1; ++i){
            dp[i][j] = dp[i][j-1] + dist2(j-1, j);
        }

        int best = INT_MAX;
        for(int k = 0; k < j-1; ++k){
            best = min(best, dp[k][j-1] + dist2(k, j));
        }

        dp[j-1][j] = best;
    }

    int ans = dp[n-1][n] + dist2(n-1, n);
    cout << ans;
}


int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    point.resize(n+1);
    point[0] = {0, 500};
    for(int i = 1; i <= n; ++i) cin >> point[i].first >> point[i].second;

    // x↑ 정렬
    sort(point.begin(), point.end(), [](auto &A, auto &B){
        return A.first < B.first || (A.first == B.first && A.second < B.second);
    });

    solve();
    return 0;
}
#define START pair<int,int>(0,500)

using namespace std;
int n;
int shortest = INT_MAX;
vector<int> DPtable;
vector<pair<int,int>> yacht;

int calculateDistance(pair<int,int> a, pair<int,int> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

int dp(int n) {
    int dist1 = DPtable[n-1] + calculateDistance(yacht[0], yacht[n]) + calculateDistance(yacht[n-1], yacht[n]);
    // int dist2 = DPtable[n-2] + calculateDistance(yacht[0], yacht[n]) + calculateDistance();
}

int main() {
    // ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    DPtable.resize(n, INT_MAX), yacht.resize(n+1);
    yacht[0] = START;
    for (int i = 1; i <= n; i++) {
        cin >> yacht[i].first >> yacht[i].second;
    }

    DPtable[0] = 0;
    DPtable[1] = calculateDistance(yacht[0], yacht[1]);
    dp(2);



    
}
