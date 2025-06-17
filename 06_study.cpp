#include <bits/stdc++.h>
using namespace std;
 
int n, p;
vector <int> chapter;
int max_pages = 0;
int min_pages = 0;
int ans;

bool can_make_group(int mid) {
    int group = 1;
    int sum = 0;
    for (auto c : chapter) {
        sum += c;
        if (sum > mid) {
            group++;
            sum = c;
        }
    }
    return group <= p;
}


int main(){
    cin >> n >> p;
    chapter.resize(n);
    for (auto &c : chapter){cin >> c;}
    max_pages = accumulate(chapter.begin(), chapter.end(), 0);
    min_pages = *max_element(chapter.begin(), chapter.end());

    while (min_pages <= max_pages) {
        int mid = (min_pages + max_pages) / 2;
        if (can_make_group(mid)) {
            ans = mid;
            max_pages = mid - 1;
        } else {
            min_pages = mid + 1;
        }
    }

    cout  << ans;
    return 0;
}
