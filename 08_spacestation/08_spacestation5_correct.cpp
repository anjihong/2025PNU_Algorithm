#include <bits/stdc++.h>
#define Point struct Vec3{ double x, y, z; Vec3 operator+(Vec3 o) { return {x + o.x, y + o.y, z + o.z}; } Vec3 operator-(Vec3 o) { return {x - o.x, y - o.y, z - o.z}; }Vec3 operator*(double t) { return {x * t, y * t, z * t}; }double norm() { return sqrt(x * x + y * y + z * z); }double dot(Vec3 o) { return x * o.x + y * o.y + z * o.z; }};
using namespace std;

Point

// 점 P에서 선분 CD까지 최단 거리
double point_to_segment(Vec3 P, Vec3 C, Vec3 D)
{
    Vec3 CD = D - C;
    double t = (P - C).dot(CD) / CD.dot(CD);
    t = max(0.0, min(1.0, t));
    Vec3 proj = C + CD * t;
    return (P - proj).norm();
}

int main()
{
    vector<Vec3> pts(4);
    for (auto &p : pts)
        cin >> p.x >> p.y >> p.z;
    Vec3 A = pts[0], B = pts[1], C = pts[2], D = pts[3];

    double lo = 0, hi = 1;
    for (int i = 0; i < 100; i++)
    {
        double t1 = lo + (hi - lo) / 3, t2 = hi - (hi - lo) / 3;

        Vec3 P1 = A + (B - A) * t1, P2 = A + (B - A) * t2;

        double d1 = point_to_segment(P1, C, D), d2 = point_to_segment(P2, C, D);

        if (d1 < d2)
            hi = t2;
        else
            lo = t1;
    }

    double t = (lo + hi) / 2;
    Vec3 bestP = A + (B - A) * t;
    double answer = point_to_segment(bestP, C, D);
    cout << (int)ceil(answer) << '\n';
}
