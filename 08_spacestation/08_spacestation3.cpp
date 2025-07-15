#include <bits/stdc++.h>
using namespace std;

struct Point
{
    double x, y, z;

    Point operator-(const Point &p) const
    {
        return {x - p.x, y - p.y, z - p.z};
    }

    Point operator+(const Point &p) const
    {
        return {x + p.x, y + p.y, z + p.z};
    }

    Point operator*(double t) const
    {
        return {x * t, y * t, z * t};
    }

    double dot(const Point &p) const
    {
        return x * p.x + y * p.y + z * p.z;
    }

    double dist(const Point &p) const
    {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z));
    }
};

// 점과 선분 사이 거리
double distance_point_to_segment(Point p, Point a, Point b)
{
    Point ab = b - a, ap = p - a;
    double t = ap.dot(ab) / ab.dot(ab);
    t = max(0.0, min(1.0, t));
    Point proj = a + ab * t;
    return p.dist(proj);
}

// 선분 AB와 CD 사이 최단 거리
double segment_segment_distance(Point A, Point B, Point C, Point D)
{
    Point u = B - A;
    Point v = D - C;
    Point w = A - C;

    double a = u.dot(u);
    double b = u.dot(v);
    double c = v.dot(v);
    double d = u.dot(w);
    double e = v.dot(w);
    double denom = a * c - b * b;

    double s, t;

    if (abs(denom) < 1e-10)
    {
        // 평행: 점과 선분 거리 4개 중 최소값
        return min({distance_point_to_segment(A, C, D),
                    distance_point_to_segment(B, C, D),
                    distance_point_to_segment(C, A, B),
                    distance_point_to_segment(D, A, B)});
    }

    s = (b * e - c * d) / denom;
    t = (a * e - b * d) / denom;

    // Clamp s, t to [0, 1]
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
        s = -d / a;
    }
    else if (t > 1)
    {
        t = 1;
        s = (b - d) / a;
    }

    // 최단 거리 점 계산
    Point P = A + u * s;
    Point Q = C + v * t;
    return P.dist(Q);
}
