#include <iostream>
#include "fakecoin.h"

// using namespace std;

int main() {
    // std::ios::sync_with_stdio(0), std::cin.tie(0);
    load_coins();
    std::pair<int, int> p = {1,21};
    int fake;
    while (true) {
        int start = p.first; int end = p.second; int mid = (start+end)/2;
        // std::cout << start << " " << end << std::endl;
        if (end - start == 1) {
            left[start] = 1; right[end] = 1;
            // std::cout << balance(left, right) << std::endl;
            fake = balance(left,right)==1 ? end : start; 
            report_coin(fake);
        }
        else {
            for (int i = start; i <= end; i++) {
                if (i <= end/2) left[i] = 1;
                else {
                    if (i == end && end%2 ) continue;
                    right[i] = 1;
                }
            }
            int w = balance(left, right);
            // std::cout << w << std::endl;
            if (w == -1) p.second = mid+1;
            else if(w == 1) p.first = mid+1;
            else if (!w) {
                fake = end;
                break;
            }
            for (int i = 0; i <22; i++) left[i] = right[i] = 0;
        }
    }
    report_coin(fake);

    return 0;
}