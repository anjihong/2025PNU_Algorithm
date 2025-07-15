#include <bits/stdc++.h>
#define Z 10000
#define M 40000
#define MIDRUN return {(a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2};
#define DISTRUN double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z; return sqrt(dx * dx + dy * dy + dz * dz);
using namespace std;

struct P
{
    double x, y, z;
};

double dist(P a, P b) {DISTRUN}

P mid(P a, P b){MIDRUN}

P nearest(P p, P a, P b)
{
    P m = mid(a, b);
    double d1 = dist(p, a), d2 = dist(p, b);
    if (d1 < d2)
        return nearest(p, a, m);
    else if (d1 > d2)
        return nearest(p, m, b);
    else
        return m;
}

int solve(double d, P p, P a, P b, P c, P e)
{
    P np = nearest(p, a, b);
    double nd = dist(np, p);
    return d > nd ? solve(nd, np, c, e, a, b) : ceil(nd);
}

int main()
{
    P pts[4];
    for (int i = 0; i < 4; i++)
        cin >> pts[i].x >> pts[i].y >> pts[i].z;
    cout << solve(M, pts[0], pts[2], pts[3], pts[0], pts[1]);
}
