#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> arr(1001, vector<int>(1001)), prefix(1001, vector<int>(1001));
int n, m, k;
pair<int, int> ans = {0, 0};

// 부분합 계산
void computePrefix()
{
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] = arr[i][j] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }
}

// 주어진 크기 k에 대해 가능한지 확인하는 함수
bool check(int k)
{
    for (int j = k; j <= n; j++) {
        for (int i = m; i >= k; i--) {
            int total = prefix[i][j] - prefix[i - k][j] - prefix[i][j - k] + prefix[i - k][j - k];
            if (total <= 1) { 
                ans = {i, j};
                return true;
            }
        }
    }
    return false;
}

void solve()
{
    int low = 1, high = min(m, n);

    while (low <= high) {
        int mid = (low + high) / 2;
        if (check(mid)) {
            k = mid;
            low = mid + 1;
        }
        else high = mid - 1;
    }
}

int main()
{
    cin >> m >> n;

    for (int i = 1; i <= m; i++) {
        string s; cin >> s;
        for (int j = 1; j <= n; j++) arr[i][j] = (s[j - 1] == '1');
    }

    computePrefix();
    solve();

    cout << ans.second - k + 1 << " " << m - ans.first + 1 << "\n" << k ;
}
