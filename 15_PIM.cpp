#include <bits/stdc++.h>
using namespace std;


int Vnum, Enum;
vector<pair<int, int>> Vvec;
vector<vector<pair<int, int>>> edgeAndDist;
vector<bool> visited;



int dist(pair<int, int> &a, pair<int, int> &b) {
    return floor(sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2)));
}

void dfs(int curV, int totalDist, vector<int> &path) {
    if (totalDist == 42) {
        for (auto &p : path) cout << p << " ";
        exit(0);
    } 
    else if (totalDist > 42) return;

    visited[curV] = true;
    path.push_back(curV);
    for (auto &next : edgeAndDist[curV]) {
        if (!visited[next.first]) {
            dfs(next.first, totalDist + next.second, path);
        }
    }
    visited[curV] = false;
    path.pop_back();
    
    if (curV == Vnum - 1 && totalDist < 42) {
        cout << -1;
        exit(1);
    }

    dfs(curV+1, totalDist, path);

};




int main() {
    // ios::sync_with_stdio(0), cin.tie(0);
    int n, from, to;
    
    
    cin >> Vnum;
    Vvec.resize(Vnum); edgeAndDist.resize(Vnum); visited.resize(Vnum);    
    for (pair<int,int> &v : Vvec) cin >> n >> v.first >> v.second;

    cin >> Enum;
    while (Enum--) {
        cin >> n >> from >> to;
        edgeAndDist[from].push_back({to, dist(Vvec[from], Vvec[to])});
    }

    vector<int> path;
    dfs(0, 0, path);
}