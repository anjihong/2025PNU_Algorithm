#include <bits/stdc++.h>

using namespace std;

struct point {
    int x, y;
    int calcDist(point other) {
        return floor(sqrt(pow(x - other.x, 2) + pow(y - other.y, 2)));
    }
};



int Vnum, Enum;
vector<point> Vvec;
vector<vector<pair<int, int>>> edgeAndDist;
vector<bool> visited;

set<int,greater<int>> bestEdges {0};
vector<int> bestPath = {0, INT_MAX};


bool isBetter(vector<int> path, set<int,greater<int>> edges) {
    if (bestPath.size() == path.size()) {
        if (bestEdges == edges) {
            return bestPath > path;
        }
        return bestEdges > edges;
    }
    return bestPath.size() < path.size(); // 더 많은 정점이 우선


}

void dfs(int curV, int totalDist, vector<int>& path, set<int,greater<int>>& edges) {
    if (totalDist > 42) return; // 목표 거리 초과

    if (curV == 0 && totalDist == 42 && path.size() > 1) {
        if (isBetter(path,edges)) {
            bestEdges = edges;
            bestPath = path;
        }
        return;
    }

    for (auto &[nextV, dist] : edgeAndDist[curV]) {
        if (nextV == 0 && path.size() > 1 && totalDist + dist == 42) {
            path.push_back(0);
            edges.insert(dist);
            dfs(0, totalDist + dist, path, edges);
            path.pop_back();
            edges.erase(dist);
        } else if (find(path.begin(), path.end(), nextV) == path.end()) { // 방문하지 않은 정점
            path.push_back(nextV);
            edges.insert(dist);
            dfs(nextV, totalDist + dist, path, edges);
            path.pop_back();
            edges.erase(dist);
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, v1, v2;
    
    cin >> Vnum;
    Vvec.resize(Vnum); edgeAndDist.resize(Vnum);
    for (point &p : Vvec) {
        cin >> n >> p.x >> p.y;
    }

    cin >> Enum;
    while (Enum--) {
        point p;
        cin >> n >> v1 >> v2;
        edgeAndDist[v1].push_back({v2, Vvec[v1].calcDist(Vvec[v2])});
        edgeAndDist[v2].push_back({v1, Vvec[v2].calcDist(Vvec[v1])});
    }

    set<int,greater<int>> edges;
    vector<int> path = {0};
    dfs(0, 0, path, edges);

    for (int i : bestPath) {
        cout << i << " ";
    }

}