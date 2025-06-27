#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double PI = acos(-1);
const double EPS = 1e-9;

struct Point { int x, y; };
pair<int,int> ans = {0,0};
int N; 

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N;
    vector<Point> P(N);
    for (Point &p : P) cin >> p.x >> p.y;
    

    int half = (N-2)/2;
    ll bestDist = -1;

    vector<double> angles;
    angles.reserve(2*(N-1));

    for(int i=0;i<N;i++){
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
                 return a.second < b.second;
             });
        int M = V.size();
        // 2) 각도 배열 두 번 이어 붙이기
        angles.resize(2*M);
        for(int k=0;k<M;k++){
            angles[k]   = V[k].first;
            angles[k+M] = V[k].first + 2*PI;
        }
        // 3) 각 j에 대해 lower_bound로 π만큼 회전한 지점 찾기
        for(int j=0;j<M;j++){
            if(j+1<M && fabs(V[j+1].first - V[j].first) < EPS) 
                continue;
            double target = V[j].first + PI;
            auto it = lower_bound(angles.begin(), angles.end(), target);
            if(it != angles.end() && fabs(*it - target) < EPS)
                continue;
            int idxLB = int(it - angles.begin());
            int cntLeft = idxLB - (j + 1);
            if(cntLeft != half) 
                continue;

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
