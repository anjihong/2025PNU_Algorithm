#include "twofakes.h"
#include <bits/stdc++.h>

std::vector<int> fake_coins;
int equal_cnt = 0;

void clear() {
    for (int i = 1; i < 11; i++) { left[i] = 0; right[i] = 0; }
}

void group(int start, int step) {
    for (int i = start; i < start + step; i++) left[i] = 1;
    for (int i = start + step; i < start + step*2; i++) right[i] = 1;
}

void recursion(int start, int step) {
    int weight;
    group(start, step); weight = balance(left, right); clear();
    
    if (step == 1) {
        if      (weight == -1) fake_coins.push_back(start);
        else if (weight ==  1) fake_coins.push_back(start+1);
        else if (weight ==  0) {fake_coins.push_back(start); fake_coins.push_back(start+1);}
        return;
    }

    if      (weight == -1) recursion(start, step/2);
    else if (weight ==  1) recursion(start+step, step/2);
    else if (weight ==  0) {
        equal_cnt ++;
        if (equal_cnt == 2) {
            fake_coins.push_back(start+4);
            equal_cnt --;
            return;
        }
        recursion(start, step/2);
        recursion(start+step, step/2);
    }
}


int main() {
    load_coins();
    recursion(1, 5);
    fake_coins[0] < 6 ? fake_coins.push_back(5) : fake_coins.push_back(10);
    two_fakes(fake_coins[0], fake_coins[1]);
}