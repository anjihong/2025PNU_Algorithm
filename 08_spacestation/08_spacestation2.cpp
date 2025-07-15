#include <bits/stdc++.h>
using namespace std;

struct point
{
    double x, y, z;

    point operator-(const point &p) const
    {
        return {x - p.x, y - p.y, z - p.z};
    }
    point operator+(const point &p) const
    {
        return {x + p.x, y + p.y, z + p.z};
    }
    point operator*(double t) const
    {
        return {x * t, y * t, z * t};
    }
    double dot(const point &p) const
    {
        return x * p.x + y * p.y + z * p.z;
    }
    double distance(const point &p) const
    {
        return sqrt((x - p.x) * (x - p.x) +
                    (y - p.y) * (y - p.y) +
                    (z - p.z) * (z - p.z));
    }
};

double distance_point_to_segment(const point &P, const point &A, const point &B)
{
    point AB = B - A;
    double ab2 = AB.dot(AB);
    if (ab2 < 1e-9)
        return P.distance(A);
    double t = (P - A).dot(AB) / ab2;
    t = max(0.0, min(1.0, t));
    return P.distance(A + AB * t);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<point> points(4);
    for (auto &p : points)
    {
        cin >> p.x >> p.y >> p.z;
    }

    point A = points[0], B = points[1], C = points[2], D = points[3];
    point u = B - A, v = D - C, w = A - C;
    double a = u.dot(u), b = u.dot(v), c = v.dot(v), d = u.dot(w), e = v.dot(w);
    double denom = a * c - b * b;

    if (fabs(denom) < 1e-9)
    {
        // 평행한 경우: 각 선분의 양 끝점에서 다른 선분까지의 최단 거리를 계산한 후 최소값 사용
        double d1 = distance_point_to_segment(C, A, B);
        double d2 = distance_point_to_segment(D, A, B);
        double d3 = distance_point_to_segment(A, C, D);
        double d4 = distance_point_to_segment(B, C, D);
        double mindist = min({d1, d2, d3, d4});
        cout << ceil(mindist) << "\n";
    }
    else
    {
        double s = (b * e - c * d) / denom;
        double t = (a * e - b * d) / denom;
        if (s < 0)
        {
            s = 0;
            t = e / c;
        }
        else if (s > 1)
        {
            s = 1;
            t = (e + b) / c;
        }
        if (t < 0)
        {
            t = 0;
        }
        else if (t > 1)
        {
            t = 1;
        }
        point P = A + u * s;
        point Q = C + v * t;
        cout << ceil(P.distance(Q)) << "\n";
    }

    return 0;
}
