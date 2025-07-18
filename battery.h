#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>

#define MAX_CNT 34

int xlim, ylim, call_cnt = 0;

FILE* in;
FILE* out;

void ready() {
    in = fopen("05.inp", "r");
    fscanf(in, "%d %d", &xlim, &ylim);
}

int experiment(int x, int y) {
    call_cnt += 1;

    if (call_cnt > MAX_CNT) {
        printf("%d", -900);
        exit(0);
    }

    if (x > xlim || y > ylim) return -1;
    else return 1;
}

void report_maxE(long value) {
    out = fopen("05.out", "w");

    if (value == ((xlim + ylim) * (xlim + ylim))) {
        fprintf(out, "%ld", value);
        exit(0);
    }
    else printf("%d", -999) ;
}
