#include <bits/stdc++.h>

using namespace std;

int k;
int min_p, min_f, min_s, min_v;

struct Food {
    int p, f, s, v, c;
};

vector<Food> Foods;
vector<int> ans, selected;
int bestCost = INT_MAX;
int bestCal = 0;

void backtrack(int idx, int p_sum, int f_sum, int s_sum, int v_sum, int cost) {
    if (p_sum >= min_p && f_sum >= min_f && s_sum >= min_s && v_sum >= min_v) {
        int totalCal = p_sum + f_sum + s_sum + v_sum;
        if (cost < bestCost ||
            (cost == bestCost && totalCal > bestCal) ||
            (cost == bestCost && totalCal == bestCal && selected < ans)) {
            bestCost = cost;
            bestCal = totalCal;
            ans = selected;
            return;
        }
    }

    if (idx >= k) return;

    // 1. 현재 재료 선택하지 않음
    backtrack(idx + 1, p_sum, f_sum, s_sum, v_sum, cost);

    // 2. 현재 재료 선택함
    selected.push_back(idx + 1);
    Food& ing = Foods[idx];
    backtrack(idx + 1, p_sum + ing.p, f_sum + ing.f, s_sum + ing.s, v_sum + ing.v, cost + ing.c);
    selected.pop_back(); // 상태 복구
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> k >> min_p >> min_f >> min_s >> min_v;

    Foods.resize(k);
    for (auto &f : Foods) cin >> f.p >> f.f >> f.s >> f.v >> f.c;
    
    backtrack(0, 0, 0, 0, 0, 0);

    if (ans.empty()) {
        cout << "0";
    } else for (int i : ans) cout << i << ' ';
    
}
