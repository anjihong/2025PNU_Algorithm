#include <bits/stdc++.h>
#define PI 3.14159265358979323846
using namespace std;

struct circle
{
    int x, y, r;
    double common_circle(circle &other)
    {
        double d = hypot(x - other.x, y - other.y);
        if (d >= r + other.r)
            return 0.0;
        else if (d <= abs(r - other.r))
            return PI * min(r, other.r) * min(r, other.r);
        else
        {
            double angle1 = acos((pow(r, 2) + pow(d, 2) - pow(other.r, 2)) / (2 * r * d));
            double angle2 = acos((pow(other.r, 2) + pow(d, 2) - pow(r, 2)) / (2 * other.r * d));
            double area1 = angle1 * r * r;
            double area2 = angle2 * other.r * other.r;
            double area3 = 0.5 * sqrt((-d + r + other.r) * (d + r - other.r) * (d - r + other.r) * (d + r + other.r));
            return area1 + area2 - area3;
        }
    }
};

int main()
{
    int n;
    cin >> n;
    vector<circle> circles(n);
    int dummy;
    for (int i = 0; i < n; ++i)
    {
        cin >> dummy >> circles[i].x >> circles[i].y >> circles[i].r;
    }

    sort(circles.begin(), circles.end(), [](circle &a, circle &b)
         {
             return a.x < b.x; // x 기준으로 정렬
         });

    double max_area = 0.0;
    int idx1 = -1, idx2 = -1;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            // x 좌표 거리만으로 겹침 여부 미리 판단
            if (circles[j].x - circles[i].x > circles[i].r + circles[j].r)
                break;

            double area = circles[i].common_circle(circles[j]);
            double cut_area = floor(area * 1000) / 1000;
            double max_cut = floor(max_area * 1000) / 1000;

            if (cut_area > max_cut || (cut_area == max_cut && make_pair(i + 1, j + 1) < make_pair(idx1, idx2)))
            {
                max_area = cut_area;
                idx1 = i + 1;
                idx2 = j + 1;
            }
        }
    }

    cout << idx1 << " " << idx2 << endl;
}
