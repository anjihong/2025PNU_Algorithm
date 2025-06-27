#include <bits/stdc++.h>
using namespace std;

struct point { 
    int x, y; 
};

int signarea(point a, point b, point c) {
    int area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return (area > 0) - (area < 0); 
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int N; cin >> N;
    vector<point> P(N);
    for (point &p : P) cin >> p.x >> p.y;

    int half = (N - 2) / 2;
    long long bestD2 = -1;
    int ansi = 0, ansj = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int cntL = 0, cntR = 0;
            bool ok = true;
            for (int k = 0; k < N; k++) {
                if (k == i || k == j) continue;
                int s = signarea(P[i], P[j], P[k]);
                if (s == 0) { 
                    ok = false;
                    break;
                }
                else if (s > 0) cntL++;
                else            cntR++;
            }
            if (cntL != half) continue;

            int dx = P[i].x - P[j].x, dy = P[i].y - P[j].y;
            int dist = dx*dx + dy*dy;
            if (dist > bestD2) {
                bestD2 = dist;
                ansi = i + 1;
                ansj = j + 1;
            }
        }
    }

    if (bestD2 < 0) cout << "0 0\n";
    else cout << ansi << " " << ansj << "\n";

    return 0;
}
