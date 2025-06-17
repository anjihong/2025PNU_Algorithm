#include <bits/stdc++.h>
#include "battery.h"

int binarySearch(bool is_x, int low, int high) {
    int ans = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        if ((is_x?experiment(mid, 0) : experiment(0, mid)) == 1) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    ready();
    int x = binarySearch(true, 0, 100000);
    int y = binarySearch(false, 0, 100000);
    report_maxE((x + y) * (x + y));
}

