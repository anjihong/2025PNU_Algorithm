#include <bits/stdc++.h>

using namespace std;
int n, t, k, Max, diff = INT_MAX; 

struct task {
    int profit;
    int deadline;
};

vector<vector<int>> schedule;
vector<task> tasks;
vector<task> not_use;


// 이익이 가장 큰 작업, 같다면 마감기한이 빠른 작업
bool compare(task a, task b) { 
    if (a.profit == b.profit) return a.deadline < b.deadline;
    return a.profit > b.profit;
}

// 작업이 스케줄에 들어 갈 수 있는지 확인, 못들어 간다면 not_use에 넣기
void check_schedule(task t) {
    for (int i = t.deadline - 1; i >= 0; i--) { 
        for (int j = 0; j < k; j++){
            if (!schedule[j][i]) {
                schedule[j][i] = t.profit;
                Max += t.profit;
                if (t.profit < diff) diff = t.profit;
                return;
            }
        }
    }
    not_use.push_back(t);
}

// 스케쥴 만들기
void make_first_schedule() {
    for (task t : tasks) {
        check_schedule(t);
    }
}

//차순위 구하기기
void make_second_schedule() {
    for (task t : not_use) {
        for (int i = t.deadline - 1; i >= 0; i--) { 
            for (int j = 0; j < k; j++) {
                int curDiff = schedule[j][i] - t.profit;    
                if (curDiff < diff && curDiff > 0) diff = curDiff;
            }
        }
    }
    
}


int main() {
    // ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> t >> k;
    
    schedule.resize(k, vector<int>(t,0));
    tasks.resize(n);

    for (task &t : tasks) cin >> t.profit >> t.deadline;
    sort(tasks.begin(), tasks.end(), compare);
    
    make_first_schedule();
    make_second_schedule();

    cout << Max << " " << Max-diff;
    
    
}