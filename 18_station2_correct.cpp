#include <bits/stdc++.h>
using namespace std;

struct Circle
{
    int id;
    double x, y, r;
};

struct Event
{
    double x;
    int type, idx;  // index into circles
    bool operator<(const Event &o) const
    {
        return x < o.x || (x == o.x && type < o.type);
    }
};

vector<Circle> circles;

double common_circle(int i, int j)
{
    auto &A = circles[i], &B = circles[j];
    double dx = A.x - B.x, dy = A.y - B.y;
    double d = sqrt(dx * dx + dy * dy);
    if (d >= A.r + B.r) return 0.0;
    if (d <= fabs(A.r - B.r)) return acos(-1) * min(A.r, B.r) * min(A.r, B.r);
    double r1 = A.r, r2 = B.r;
    double alpha = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
    double beta = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
    double seg = 0.5 * sqrt(max(0.0, (-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2)));
    return r1 * r1 * alpha + r2 * r2 * beta - seg;
}

int main()
{
    int N; cin >> N;
    circles.resize(N);
    vector<Event> events;
    events.reserve(2 * N);

    // 입력 및 이벤트 생성
    for (int i = 0; i < N; i++)
    {
        cin >> circles[i].id >> circles[i].x >> circles[i].y >> circles[i].r;
        events.push_back({circles[i].x - circles[i].r, 1, i});
        events.push_back({circles[i].x + circles[i].r, 2, i});
    }
    sort(events.begin(), events.end());

    vector<int> active;
    double bestA = -1.0;
    int R1 = 0, R2 = 0;
    double EPS = 1e-12;

    // 라인 스위프
    for (auto &ev : events)
    {
        int i = ev.idx;
        if (ev.type == 1)
        {
            for (int j : active)
            {
                double raw = common_circle(i, j);
                double A = floor(raw * 1000.0) / 1000.0;
                int id1 = min(circles[i].id, circles[j].id);
                int id2 = max(circles[i].id, circles[j].id);
                if (A > bestA + EPS ||
                    (fabs(A - bestA) < EPS && make_pair(id1, id2) < make_pair(R1, R2)))
                {
                    bestA = A;
                    R1 = id1;
                    R2 = id2;
                }
            }
            active.push_back(i);
        }
        else
        {
            auto it = find(active.begin(), active.end(), i);
            if (it != active.end())
                active.erase(it);
        }
    }

    cout << R1 << " " << R2 << "\n";
    return 0;
}
