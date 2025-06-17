#include <bits/stdc++.h>
#include "fakecoin.h"


void clear() {
    for (int i = 0; i <22; i++) { left[i] = 0; right[i] = 0; }
}

void group(int start, int step) {
    for (int i = start; i < start + step; i++) left[i] = 1;
    for (int i = start + step; i < start + step*2; i++) right[i] = 1;
}

void recursion(int start, int step) {
    int weight;
    group(start, step); weight = balance(left, right); clear();

    if (step == 1) {
        if (weight == -1) report_coin(start);
        else if (weight == 1) report_coin(start+1);
        else if (weight == 0) report_coin(start+2);
    }


    if (weight == -1) recursion(start, step/2);
    else if (weight == 1) recursion(start+step, step/2);
    else if (weight == 0) {
        if (step == 3) report_coin(start+step*2);
        recursion(start+step*2, step/2);
    }
}

int main() {
    // std::ios::sync_with_stdio(0), std::cin.tie(0);
    load_coins();
    recursion(1, 7);
}