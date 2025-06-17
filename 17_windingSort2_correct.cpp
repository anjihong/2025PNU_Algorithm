#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y, idx;
    bool used = false;

    long long distance(Point other) {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }
};

vector<Point> points;
Point prevPoint = {-1,0,-1}, curPoint = {0,0,-1};
int N;

long long dot(Point p) {
    return (curPoint.x - prevPoint.x) * (p.x - curPoint.x) +
           (curPoint.y - prevPoint.y) * (p.y - curPoint.y);
}

long long signed_area(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() {
    cin >> N; points.resize(N);
    for (auto &p : points) {
        cin >> p.idx >> p.x >> p.y;
    }

    for(int i = 0; i < N; i++) {
        int bestIdx = -1;
        for (int j = 0; j < N; j++) {
            if (points[j].used) continue;
            if (bestIdx < 0) {
                bestIdx = j;
                continue;
            }

            long long prevArea = signed_area(prevPoint, curPoint, points[bestIdx]);
            long long curArea = signed_area(prevPoint, curPoint, points[j]);

            if ((prevArea^curArea) < 0 && curArea >= 0) bestIdx = j;
            
            else {
                long long left_side = dot(points[bestIdx]) * abs(curArea);
                long long right_side = dot(points[j]) * abs(prevArea);

                if(left_side < right_side) {
                    bestIdx = j;
                }
                else if (right_side == left_side) {
                    if (points[j].distance(curPoint) < points[bestIdx].distance(curPoint)) {
                        bestIdx = j;
                    }
                }   
            }
        }
        points[bestIdx].used = true;
        prevPoint = curPoint;
        curPoint = points[bestIdx];
        cout << points[bestIdx].idx << "\n";
    }
}