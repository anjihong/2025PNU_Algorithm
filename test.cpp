#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    set<int, greater<int>> s = {1, 2, 3, 4, 5};
    set<int, greater<int>> s2 = {3, 4, 5, 6, 7};

    cout << (s < s2) << endl; // true


}