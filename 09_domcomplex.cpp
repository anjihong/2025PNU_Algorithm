#include <bits/stdc++.h>

using namespace std;
vector<vector<int>> arr(1001, vector<int>(1001)), prefix(1001, vector<int>(1001));


int n, m;
int k;
pair<int, int> ans = {0, 0};


void find(int low, int high) {
    if (low > high) return;
    int mid = (low + high) / 2;
    cout << "mid: " << mid << "\n";
    for (int j = mid; j <= n; j++){
        for (int i = m; i >= m-mid; i--) {
            cout << "here\n";
            cout << "" << i << " " << j << "\n";
            int num = prefix[i][j] - prefix[i-mid][j] - prefix[i][j-mid] + prefix[i-mid][j-mid];
            cout << "num: " << num << "\n";
            if (num > 1) {
                return find(low, mid-1);
            }
            else {
                ans = {i, j};
                k = mid;
                return find(mid+1, high);
            }
        }
    }
}

int main() {
    // ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m; cin.ignore();

    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            arr[i+1][j+1] = (s[j] == '1');
        }
    }


    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            prefix[i][j] = arr[i][j];
            if (i > 1)
                prefix[i][j] += prefix[i - 1][j];
            if (j > 1)
                prefix[i][j] += prefix[i][j - 1];
            if (i > 1 && j > 1)
                prefix[i][j] -= prefix[i - 1][j - 1];
        }
    }


    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cout << prefix[i][j] << " ";
        }
        cout << "\n";
    }

    int low = 1; int high = min(m, n);
    find(low, high);
    cout << ans.second - k + 1 << " " << n - ans.first + 1 << "\n";
    cout << k << "\n";
}