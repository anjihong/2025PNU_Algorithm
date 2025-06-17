#include <bits/stdc++.h>

using namespace std;
struct point {
    double x, y, z;
    
    point operator-(point p) {
        return {x - p.x, y - p.y, z - p.z};
    }

    point operator*(double t) {
        return {x * t, y * t, z * t};
    }

    point operator+(point p) {
        return {x + p.x, y + p.y, z + p.z};
    }

    double dot(point p) {
        return x * p.x + y * p.y + z * p.z;
    }

    double distance(point p) {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) + (z - p.z) * (z - p.z));
    }
};

double distance_point_to_segment(point P, point A, point B)
{
    point AB = B - A, AP = P - A;
    double ab2 = AB.dot(AB);
    if (ab2 < 1e-9) return P.distance(A); // A와 B가 거의 같은 경우
    double t = max(0.0, min(1.0, AP.dot(AB) / ab2));
    return P.distance(A + AB * t);
};

int main() {
    vector <point> points(4);
    double min_dist = 0;
    for (auto &p : points) {cin >> p.x >> p.y >> p.z;}

    point A = points[0], B = points[1], C = points[2], D = points[3];
    point u = B - A, v = D - C, w = A - C;
    double a = u.dot(u), b = u.dot(v), c = v.dot(v), d = u.dot(w), e = v.dot(w);

    double denom = a * c - b * b;
    if (!denom) {
        min_dist = min({distance_point_to_segment(A, C, D), distance_point_to_segment(B, C, D),
                    distance_point_to_segment(C, A, B), distance_point_to_segment(D, A, B)});
    }
    else {
        double s = (b * e - c * d) / denom;
        s < 0 ? s = 0 : s > 1 ? s = 1 : s = s;
        
        double t = (a * e - b * d) / denom;
        t < 0 ? t = 0 : t > 1 ? t = 1 : t = t;

        point P = A + (u * s);
        point Q = C + (v * t);
        min_dist = ceil(P.distance(Q));
    }
    cout << min_dist;



}