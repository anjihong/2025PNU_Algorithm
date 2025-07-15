#include <bits/stdc++.h>
#define TARGET 42
#define START 0
using namespace std;

int Vnum, Enum;
vector<pair<int, int>> Vvec;
vector<vector<pair<int, int>>> edgeAndDist;
vector<bool> visited;


vector<int> bestPath, bestEdge;

int getDist(pair<int, int> a, pair<int, int> b)
{
    return floor(sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2)));
}

// 비교 기준: 1. 더 많은 정점, 2. edge 길이들 사전순
bool isBetter(const vector<int> &path, const vector<int> &edge)
{
    if (path.size() > bestPath.size()) return true;
    if (path.size() < bestPath.size()) return false;
    
    int curStart = path[1]; // 항상 0 다음 정점
    int bestStart = bestPath[1];

    if (curStart < bestStart) return true;
    if (curStart > bestStart) return false;

    // 출발 정점이 동일하면, edge 길이들 사전순 비교
    return edge < bestEdge;
}

void dfs(int curV, int totalDist, vector<int> &path, vector<int> &edgeSeq)
{
    if (totalDist > TARGET)
        return;

    // 싸이클 완성 조건
    if (curV == START && totalDist == TARGET && path.size() > 1)
    {
        
        if (isBetter(path, edgeSeq))
        {
            bestPath = path;
            bestEdge = edgeSeq;
        }
        return;
    }

    for (auto &[nextV, dist] : edgeAndDist[curV])
    {
        if (nextV == START && path.size() > 1 && totalDist + dist == TARGET)
        {
            path.push_back(START);
            edgeSeq.push_back(dist);
            dfs(START, totalDist + dist, path, edgeSeq);
            path.pop_back();
            edgeSeq.pop_back();
        }
        else if (!visited[nextV] && totalDist + dist < TARGET)
        {
            visited[nextV] = true;
            path.push_back(nextV);
            edgeSeq.push_back(dist);
            dfs(nextV, totalDist + dist, path, edgeSeq);
            path.pop_back();
            edgeSeq.pop_back();
            visited[nextV] = false;
        }
    }
}

int main()
{
    cin >> Vnum;
    Vvec.resize(Vnum);
    edgeAndDist.resize(Vnum);
    visited.resize(Vnum);

    int idx, x, y;
    for (int i = 0; i < Vnum; ++i)
    {
        cin >> idx >> x >> y;
        Vvec[idx] = {x, y};
    }

    cin >> Enum;
    int edgeIdx, from, to;
    for (int i = 0; i < Enum; ++i)
    {
        cin >> edgeIdx >> from >> to;
        int d = getDist(Vvec[from], Vvec[to]);
        edgeAndDist[from].push_back({to, d});
        edgeAndDist[to].push_back({from, d}); // 양방향 간선 처리
    }

    visited[START] = true;
    vector<int> path = {START}, edgeSeq;
    dfs(START, 0, path, edgeSeq);

    if (bestPath.empty())
    {
        cout << -1 << endl;
    }
    else
    {
        for (int v : bestPath)
            cout << v << " ";
        cout << endl;
    }

    return 0;
}
