#include <bits/stdc++.h>
#define PI 3.14159265358979323846
using namespace std;

struct circle
{
    double x, y, r;
    int id;
    double common_circle(circle &other)
    {
        double dx = x - other.x, dy = y - other.y;
        double d = sqrt(dx * dx + dy * dy);
        if (d >= r + other.r) return 0.0; // 겹치지 않음
        if (d <= fabs(r - other.r)) return PI * min(r, other.r) * min(r, other.r); // 한 원이 다른 원을 포함함
        double r1 = r, r2 = other.r;
        double alpha = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
        double beta = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
        double seg = 0.5 * sqrt(max(0.0, (-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2)));
        return r1 * r1 * alpha + r2 * r2 * beta - seg; // 겹치는 부분의 면적
    }
};

int main()
{
    int n;
    cin >> n;
    vector<circle> circles(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> circles[i].id >> circles[i].x >> circles[i].y >> circles[i].r;
    }

    sort(circles.begin(), circles.end(), [](circle &a, circle &b) {return a.x < b.x; });

    double max_area = 0.0;
    int idx1 = INT_MAX, idx2 = INT_MAX;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            // x 좌표 거리만으로 겹침 여부 미리 판단
            if (circles[j].x - circles[i].x > circles[i].r + circles[j].r)
                continue;

            double area = circles[i].common_circle(circles[j]);
            double cut_area = floor(area * 1000) / 1000;
            double max_cut = floor(max_area * 1000) / 1000;
            
            int id1, id2;
            circles[i].id < circles[j].id ? (id1 = circles[i].id, id2 = circles[j].id)
                                           : (id1 = circles[j].id, id2 = circles[i].id);
            if (cut_area > max_cut || (cut_area == max_cut && make_pair(id1, id2) < make_pair(idx1, idx2)))
            {
                max_area = cut_area;
                idx1 = id1;
                idx2 = id2;
            }
        }
    }

    cout << idx1 << " " << idx2 << endl;
}
