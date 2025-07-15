#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll signed_area(ll ax, ll ay, ll bx, ll by, ll cx, ll cy)
{
    return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

int main()
{
    int N;
    cin >> N;

    vector<int> idx(N);
    vector<ll> X(N), Y(N);
    for (int i = 0; i < N; i++)
    {
        cin >> idx[i] >> X[i] >> Y[i];
    }

    vector<bool> used(N, false);
    ll curX = 0, curY = 0;             // 현재 기준점 (처음엔 원점)
    ll prevX = curX - 1, prevY = curY; // 이전 기준점 → 초기 방향 벡터는 (1,0)

    vector<int> result;
    result.reserve(N);

    for (int step = 0; step < N; step++)
    {
        int best = -1;
        for (int j = 0; j < N; j++)
        {
            if (used[j])
                continue;
            if (best < 0)
            {
                best = j;
                continue;
            }

            ll area_best = signed_area(prevX, prevY, curX, curY, X[best], Y[best]);
            ll area_j = signed_area(prevX, prevY, curX, curY, X[j], Y[j]);

            bool half_best = (area_best < 0); // 음수면 2π회전 구간(>180°)
            bool half_j = (area_j < 0);

            if (half_best != half_j)
            {
                if (!half_j)
                    best = j;
            }
            else
            {
                // 2) 둘 다 같은 반회전 구간일 때: atan2 대신 cross/dot 비교
                ll dx = curX - prevX, dy = curY - prevY;
                ll vx_b = X[best] - curX, vy_b = Y[best] - curY;
                ll vx_j = X[j] - curX, vy_j = Y[j] - curY;

                ll dot_b = dx * vx_b + dy * vy_b;
                ll dot_j = dx * vx_j + dy * vy_j;

                __int128 lhs = (__int128)llabs(area_j) * dot_b;
                __int128 rhs = (__int128)llabs(area_best) * dot_j;
                if (lhs < rhs)
                {
                    best = j;
                }
                else if (lhs == rhs)
                {
                    ll dist_b = vx_b * vx_b + vy_b * vy_b;
                    ll dist_j = vx_j * vx_j + vy_j * vy_j;
                    if (dist_j < dist_b)
                        best = j;
                }
            }
        }

        // 선택된 점 출력
        result.push_back(idx[best]);
        used[best] = true;

        // 기준점 갱신
        prevX = curX;
        prevY = curY;
        curX = X[best];
        curY = Y[best];
    }

    // 결과 출력
    for (int id : result)
    {
        cout << id << "\n";
    }
}
