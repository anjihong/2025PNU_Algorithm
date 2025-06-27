#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double PI = acos(-1);
const double EPS = 1e-9;

struct Point { ll x, y; };

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<Point> P(N);
    for(int i=0;i<N;i++){
        cin >> P[i].x >> P[i].y;
    }
    if(N%2==1){
        cout << "0 0\n";
        return 0;
    }
    int half = (N-2)/2;
    ll bestDist = -1;
    pair<int,int> ans = {0,0};

    vector<double> angles;
    angles.reserve(2*(N-1));

    for(int i=0;i<N;i++){
        // 1) i 기준으로 나머지 점들의 각도 계산
        vector<pair<double,int>> V;
        V.reserve(N-1);
        for(int j=0;j<N;j++){
            if(j==i) continue;
            double th = atan2((double)(P[j].y-P[i].y),
                              (double)(P[j].x-P[i].x));
            if(th < 0) th += 2*PI;
            V.emplace_back(th, j);
        }
        sort(V.begin(), V.end(),
             [&](auto &a, auto &b){
                 if (fabs(a.first - b.first) > EPS)
                     return a.first < b.first;
                 // 같은 방향이면 인덱스 비교로 안정화
                 return a.second < b.second;
             });
        int M = (int)V.size();
        // 2) 각도 배열 두 번 이어 붙이기
        angles.resize(2*M);
        for(int k=0;k<M;k++){
            angles[k]   = V[k].first;
            angles[k+M] = V[k].first + 2*PI;
        }
        // 3) 각 j에 대해 lower_bound로 π만큼 회전한 지점 찾기
        for(int j=0;j<M;j++){
            // 동일 방향(collinear) 점 제외
            if(j+1<M && fabs(V[j+1].first - V[j].first) < EPS) 
                continue;
            double target = V[j].first + PI;
            // π 위치에 점이 있으면 collinear
            auto it = lower_bound(angles.begin(), angles.end(), target);
            if(it != angles.end() && fabs(*it - target) < EPS)
                continue;
            int idxLB = int(it - angles.begin());
            int cntLeft = idxLB - (j + 1);
            if(cntLeft != half) 
                continue;

            // 거리가 최대인지 갱신
            int jidx = V[j].second;
            ll dx = P[jidx].x - P[i].x;
            ll dy = P[jidx].y - P[i].y;
            ll d2 = dx*dx + dy*dy;
            if(d2 > bestDist){
                bestDist = d2;
                ans = { min(i,jidx)+1, max(i,jidx)+1 }; // 1-based
            }
        }
    }

    if(bestDist < 0) 
        cout << "0 0\n";
    else 
        cout << ans.first << " " << ans.second << "\n";

    return 0;
}
