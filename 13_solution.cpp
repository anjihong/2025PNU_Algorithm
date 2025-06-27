#include <bits/stdc++.h>

using namespace std;

int n,R,answer;
vector<int> nums;


void backtrack(int idx, int sum) {
    if (idx == n) {
        if (sum == R) answer = (answer + 1) % 11111;
        return;
    }

    for (int x = 1; sum + nums[idx] * x <= R; x++) {
        backtrack(idx + 1, sum + nums[idx] * x);
    }
}

int main() {
    cin >> n; nums.resize(n);
    for (auto &x : nums) cin >> x;
    cin >> R;

    backtrack(0, 0);
    cout << answer;
}
