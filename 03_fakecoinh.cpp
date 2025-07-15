#include "fakecoin.h"

void leftone(int f, int n){
    for(int i = f; i <= n; i++) ::left[i] = 1;
}

void rightone(int f, int n){
    for(int i = f; i <= n; i++) ::right[i] = 1;
}

void zero(){
    for(int i = 1; i <= 21; i++){
        ::left[i] = 0;
        ::right[i] = 0;
    }
}


int main(){
    load_coins();
    int first = 0;
    int last = 0;
    // 1~7, 8~14, 15~21 그룹으로 분할
    leftone(1, 7);
    rightone(8, 14);

    int bal = balance(::left, ::right);
    zero();

    // 1번 그룹(1~7)에 가짜가 있을 경우
    if(bal == -1){
        leftone(1, 3);
        rightone(4, 6);
        first = 1; last = 7;
    }
    // 2번 그룹(8~15)에 가짜가 있을 경우
    else if(bal == 1){
        leftone(8, 10);
        rightone(11, 13);
        first = 8; last = 14;
    }
    // 3번 그룹(16~21)에 가짜가 있을 경우
    else if(bal == 0){
        leftone(15, 17);
        rightone(18, 20);
        first = 15; last = 21;
    }

    bal = balance(::left, ::right);
    zero();

    // 후보 그룹 내에서 3개 r중 2개를 비교
    if(bal == -1){
        ::left[first] = 1;
        ::right[first + 1] = 1;
        last = first + 2;
    }
    else if(bal == 1){
        first = first + 3;
        last = first + 2;
        ::left[first] = 1;
        ::right[first + 1] = 1;        
    }
    else if(bal == 0){
        report_coin(last);
    }

    bal = balance(::left, ::right);

    if(bal == -1){
        report_coin(first);
    }
    else if(bal == 1){
        report_coin(first + 1);
    }
    else if(bal == 0){
        report_coin(last);
    }
}