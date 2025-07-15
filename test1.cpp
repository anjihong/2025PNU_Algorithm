#include <bits/stdc++.h>

using namespace std;


void add(int x, int y) {
    x ++; y++;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    
    int a = 1;
    int arr[] = {1,2,3,4,5};
    add(a, arr[a]);
    // a = 2; arr = (1,3,3,4,5)
    
    
    cout << a << " " ;
    for (auto i : arr) cout << i << " ";


}