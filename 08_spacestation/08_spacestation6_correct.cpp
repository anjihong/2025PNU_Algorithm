#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y, z;
    
    Point mid_point(Point p) {
        return {(x + p.x) / 2, (y + p.y) / 2, (z + p.z) / 2};    
    }

    double distance(Point p) {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z - p.z, 2));
    }
};

Point midP;

double shortest_distance(Point P, Point A, Point B) {
    Point mid = A.mid_point(B);
    
    double distA = P.distance(A),
           distB = P.distance(B), 
           distMid = P.distance(mid);

    if (distA == distB) { 
        midP = mid; 
        return distMid; 
    }
    else if (distA < distB) return shortest_distance(P, A, mid);
    else return shortest_distance(P, mid, B);
}




int main() {
    vector<Point> points(4);
    for (auto &p : points) {cin >> p.x >> p.y >> p.z;}

    Point A = points[0], B = points[1], C = points[2], D = points[3];
    midP = A;
    
    while (true) {
        double dist1 = shortest_distance(midP, C, D), 
               dist2 = shortest_distance(midP, A, B);
        if (dist1<=dist2) {cout << (int)ceil(dist1); break;}
    }
}