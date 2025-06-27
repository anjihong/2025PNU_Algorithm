#include <bits/stdc++.h>
// #include "DNA_bank_student.h"
#include "DNA_bank.h"
//attctataccga 1
//gatcatacctt 3
//actgctccagt 0
//ggtgggtg 4
//atttgcat  2
using namespace std;

long long xseed, Nsize;
vector<int> sorted_indices;

void bucket_sort(int depth, vector<int>& indices) {
    if (indices.size() == 0) return;
    if (indices.size() == 1) {
        sorted_indices.insert(sorted_indices.end(), indices.begin(), indices.end());
        return;
    }
    if (depth > 100) {
        sorted_indices.insert(sorted_indices.end(), indices.begin(), indices.end());
        return;
    }

    vector<int> buckets[5];
    for (int idx : indices) {
        char nucleo = DNA_base(xseed, idx, depth);
        int b = (nucleo =='$'?0 : nucleo=='a'?1 : nucleo=='c'?2 : nucleo=='g'?3 : 4);
        buckets[b].push_back(idx);
    }

    for (int i = 0; i < 5; i++) {
        if (!buckets[i].empty()) bucket_sort(depth + 1, buckets[i]);
    }
}


int main() {
    int index1, index2;
    int findx1, findx2;

    set_DNA_bank();
    Nsize = get_size();
    xseed = get_seed();

    get_index(&index1, &index2);
    // cout << "index1: " << index1 << ", index2: " << index2 << endl;

    vector<int> all(Nsize);
    iota(all.begin(), all.end(), 0);

    bucket_sort(0, all);
    // for (auto i : sorted_indices) {
    //     cout << i << " ";
    // }


    findx1 = sorted_indices[index1];
    findx2 = sorted_indices[index2];
    report(findx1, findx2);



}
