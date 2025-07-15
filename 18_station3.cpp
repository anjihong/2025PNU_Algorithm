#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);

struct Circle
{
    int id, x, y, r;
    double common_circle(const Circle &o) const
    {
        double dx = x - o.x, dy = y - o.y;
        double d = sqrt(dx * dx + dy * dy);
        if (d >= r + o.r)
            return 0.0;
        if (d <= abs(r - o.r))
            return PI * min(r, o.r) * min(r, o.r);
        double r1 = r, r2 = o.r;
        double alpha = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
        double beta = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
        double seg = 0.5 * sqrt(max(0.0, (-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2)));
        return r1 * r1 * alpha + r2 * r2 * beta - seg;
    }
};

struct Event
{
    double x;
    int type; // 1=insert, 2=remove
    int idx;  // circles index
    bool operator<(const Event &o) const
    {
        if (x != o.x)
            return x < o.x;
        return type < o.type; // insert 먼저
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Circle> circles(n);
    for (int i = 0; i < n; i++)
    {
        cin >> circles[i].id >> circles[i].x >> circles[i].y >> circles[i].r;
    }

    // 전역 최대 반지름
    double maxR = 0;
    for (auto &c : circles)
        maxR = max(maxR, (double)c.r);

    // 이벤트 생성
    vector<Event> events;
    events.reserve(2 * n);
    for (int i = 0; i < n; i++)
    {
        events.push_back({circles[i].x - circles[i].r, 1, i});
        events.push_back({circles[i].x + circles[i].r, 2, i});
    }
    sort(events.begin(), events.end());

    multiset<pair<double, int>> active; // (y, idx)
    double bestArea = -1.0;
    int ans1 = 0, ans2 = 0;
    const double EPS = 1e-12;

    // 스위프
    for (auto &ev : events)
    {
        int i = ev.idx;
        const auto &C = circles[i];
        if (ev.type == 1)
        {
            // insert
            double lo = C.y - (C.r + maxR);
            double hi = C.y + (C.r + maxR);
            auto it_lo = active.lower_bound({lo, INT_MIN});
            auto it_hi = active.upper_bound({hi, INT_MAX});
            for (auto it = it_lo; it != it_hi; ++it)
            {
                int j = it->second;
                const auto &D = circles[j];
                if (abs(C.x - D.x) > C.r + D.r)
                    continue;
                double A = C.common_circle(D);
                double Atr = floor(A * 1000.0) / 1000.0;
                auto ids = make_pair(min(C.id, D.id), max(C.id, D.id));
                if (Atr > bestArea + EPS ||
                    (fabs(Atr - bestArea) < EPS && ids < make_pair(ans1, ans2)))
                {
                    bestArea = Atr;
                    ans1 = ids.first;
                    ans2 = ids.second;
                }
            }
            active.insert({C.y, i});
        }
        else
        {
            // remove
            active.erase(active.find({C.y, i}));
        }
    }

    cout << ans1 << " " << ans2 << "\n";
    return 0;
}
