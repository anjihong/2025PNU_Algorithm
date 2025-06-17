#include <bits/stdc++.h>
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