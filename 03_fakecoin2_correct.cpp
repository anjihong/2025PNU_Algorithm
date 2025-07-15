#include <bits/stdc++.h>
#include "fakecoin.h"

int candidate;

void clear() {
    for (int i = 0; i <22; i++) { left[i] = 0; right[i] = 0; }
}

void group(int start, int step) {
    for (int i = start; i < start + step; i++) left[i] = 1;
    for (int i = start + step; i < start + step*2; i++) right[i] = 1;
}

int main() {
    // std::ios::sync_with_stdio(0), std::cin.tie(0);
    load_coins();
    
    group(1, 7);

    int weight = balance(left, right); clear();
    if (weight == -1) { group(1,3); candidate = 1; } // 왼쪽 그룹에 가짜
    else if (weight == 1) { group(8,3); candidate = 8; } // 중간 그룹에 가짜
    else if (weight == 0) { group(15,3); candidate = 15; } // 오른쪽 그룹에 가짜

    weight = balance(left, right); clear();
    if (weight == -1) { group(candidate, 1); }
    else if (weight == 1) { group(candidate+3, 1); candidate += 3; }
    else if (weight == 0) report_coin(candidate+6);

    weight = balance(left, right);
    if (weight == -1) report_coin(candidate);
    else if (weight == 1) report_coin(candidate+1);
    else report_coin(candidate+2);
}