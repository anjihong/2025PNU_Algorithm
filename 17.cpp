#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point
{
    int idx;
    ll x, y;
    bool used;
};

static inline ll signed_area(const Point &p, const Point &q, const Point &r)
{
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

int main()
{
    int N;
    cin >> N;
    vector<Point> pts(N);
    for (int i = 0; i < N; i++)
    {
        cin >> pts[i].idx >> pts[i].x >> pts[i].y;
        pts[i].used = false;
    }

    ll ax = 0, ay = 0;
    ll rx = 1, ry = 0;

    for (int t = 0; t < N; t++)
    {
        int best = -1;
        __int128 best_ux = 0, best_uy = 0;
        ll best_dx = 0, best_dy = 0, best_dist2 = 0;
        int best_h = 0;

        for (int i = 0; i < N; i++)
        {
            if (pts[i].used)
                continue;

            ll dx = pts[i].x - ax;
            ll dy = pts[i].y - ay;

            __int128 ux = (__int128)rx * dx + (__int128)ry * dy;
            __int128 uy = (__int128)rx * dy - (__int128)ry * dx;

            int h = (uy > 0 || (uy == 0 && ux > 0)) ? 0 : 1;
            ll dist2 = dx * dx + dy * dy;

            if (best < 0 || h < best_h || (h == best_h && ((best_ux * uy - best_uy * ux) < 0 || ((best_ux * uy - best_uy * ux) == 0 && dist2 < best_dist2))))
            {
                best = i;
                best_ux = ux;
                best_uy = uy;
                best_dx = dx;
                best_dy = dy;
                best_dist2 = dist2;
                best_h = h;
            }
        }

        cout << pts[best].idx << "\n";
        pts[best].used = true;

        ax = pts[best].x;
        ay = pts[best].y;
        rx = best_dx;
        ry = best_dy;
    }

    return 0;
}
