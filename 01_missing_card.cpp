#include <bits/stdc++.h>
using namespace std;

bool arr[10001];
int n; int card;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    cin >> n;
    while (cin >> card) { arr[card] = true; }

    for (int i = 1; i <= n; i++) {
        if (!arr[i]) cout << i << "\n";
    }
    return 0;
}

