#include <bits/stdc++.h>

using namespace std;
int n ;
int s1, s2;
int p1 = 0, p2 = 0;
int a, b, ans1, ans2;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    s1 = (n*(n+1))/2;
    s2 = (n*(n+1)*(2*n+1))/6;
    
    int num;
    while (cin >> num) {
        p1 += num;
        p2 += num*num;
    }

    a = s1 - p1;
    b = s2 - p2;

    cout << a << " " << b << "\n";
    if (a*a == b) {cout << a; return 0;}

    // 두 수의 합 = a, 두 수의 제곱의 합 = b, 두 수의 곱 = (a^2 - b)/2
    // x^2 - ax + (a^2 - b)/2 = 0
    // 2*x&2 - 2ax + a^2 - b = 0
    // 근의 공식 : x = (a +- sqrt(-a^2 + 2b))/2 

    else {
        int sq = sqrt(-a*a + 2*b);
        ans1 = (a - sq)/2;
        ans2 = (a + sq)/2;

        cout << ans1 << " " << ans2;
    }


}