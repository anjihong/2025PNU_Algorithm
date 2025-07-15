#include <bits/stdc++.h>

using namespace std;

int TARGET = 42, INF = 1e9;
int N, M;
vector<pair<int, int>> coords;
vector<vector<pair<int, int>>> adj;

vector<int> bestPath, bestWeights;

bool better(vector<int> &path1, vector<int> &w1,
            vector<int> &path2, vector<int> &w2)
{
    if (path1.size() != path2.size())
        return path1.size() > path2.size();
    if (*max_element(w1.begin(), w1.end()) != *max_element(w2.begin(), w2.end()))
        return *max_element(w1.begin(), w1.end()) < *max_element(w2.begin(), w2.end());
    return w1 < w2;
}

void dfs(int curr, int dist, vector<int> &path, vector<int> &weights, set<int> &visited)
{
    if (dist > TARGET)
        return;
    if (curr == 0 && dist == TARGET && path.size() > 1)
    {
        if (better(path, weights, bestPath, bestWeights))
        {
            bestPath = path;
            bestWeights = weights;
        }
        return;
    }

    for (auto [next, w] : adj[curr])
    {
        if (next == 0 && path.size() < 2)
            continue;
        if (visited.count(next))
            continue;

        path.push_back(next);
        weights.push_back(w);
        visited.insert(next);
        dfs(next, dist + w, path, weights, visited);
        visited.erase(next);
        weights.pop_back();
        path.pop_back();
    }
}

int calcDist(pair<int, int> a, pair<int, int> b)
{
    return (int)sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    coords.resize(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> coords[i].first >> coords[i].second;
    }

    cin >> M;
    adj.assign(N, {});
    for (int i = 0; i < M; ++i)
    {
        int u, v;
        cin >> u >> v;
        int d = calcDist(coords[u], coords[v]);
        adj[u].emplace_back(v, d);
        adj[v].emplace_back(u, d);
    }

    sort(adj[0].begin(), adj[0].end()); // 출발점 0에서 연결된 정점 번호 순

    for (auto [start, w] : adj[0])
    {
        vector<int> path = {0, start}, weights = {w};
        set<int> visited = {0, start};
        dfs(start, w, path, weights, visited);
    }

    if (bestPath.empty()) cout << -1;
    else
    {
        for (int v : bestPath) cout << v << ' ';
        cout << 0; // 돌아와야 함
    }

    return 0;
}
