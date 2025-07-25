#include <stdio.h>
#include <stdlib.h>
#define MAX_CNT 5

int left[11]  = {0,};
int right[11] = {0,};

char input[12];
int  coins[11];

int balance_call_cnt = 0;

FILE* in;
FILE* out;

void load_coins() {
    in = fopen("05.inp", "r");
    fscanf(in, "%11s", input);

    for (int i = 0; i < 11; i++) {
        coins[i] = input[i] - '0';
    }

    fclose(in);
}

void two_fakes(int idx1, int idx2) {
    out = fopen("05.out", "w");
    fprintf(out, "%d %d", idx1, idx2);
    exit(0);
}

int balance(int left[], int right[]) {
    balance_call_cnt += 1;
    if (balance_call_cnt > MAX_CNT) {
        out = fopen("05.out", "w");
        fprintf(out, "Function call limit over");
        exit(0);
    }

    int left_weight = 0, right_weight = 0;

    for (int i=1; i < 11; i++) {
        if (left[i] == 1 && right[i] == 1) {
            return 999;
        }
        if (left[i] != 0 && left[i] != 1) {
            return 999;
        }
        if (right[i] != 0 && right[i] != 1) {
            return 999;
        }
        if (left[i] == 1) {
            left_weight += coins[i];
        }
        if (right[i] == 1) {
            right_weight += coins[i];
        }
    }

    if (left_weight < right_weight) { return 1; }
    else if (left_weight == right_weight) { return 0; }
    else if (left_weight > right_weight) { return -1; }
}