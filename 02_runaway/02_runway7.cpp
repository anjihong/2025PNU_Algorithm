#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<string> grid;
vector<vector<int>> P; 

void computePrefix() {
    P.assign(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cell = grid[i - 1][j - 1] - '0';
            P[i][j] = cell + P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];
        }
    }
}

int query(int r1, int c1, int r2, int c2) {
    return P[r2][c2] - P[r1 - 1][c2] - P[r2][c1 - 1] + P[r1 - 1][c1 - 1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> m >> n;
    grid.resize(m);
    for (int i = 0; i < m; i++){
        cin >> grid[i];
    }
    computePrefix();
    
    int bestL = 0;
    int best_x = 5001, best_y = 5001;
    
    for (int r = 0; r < m - 1; r++) {
        for (int c = 0; c < n; c++){
            int lo = 1, hi = n - c, candidateL = 0;
            while(lo <= hi){
                int mid = (lo + hi) / 2;
                if(query(r + 1, c + 1, r + 2, c + mid) == 0){
                    candidateL = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if(candidateL > bestL){
                bestL = candidateL;
                best_x = c;
                best_y = r; 
            } else if(candidateL == bestL && candidateL > 0){
                if(c < best_x || (c == best_x && r < best_y)){
                    best_x = c;
                    best_y = r;
                }
            }
        }
    }
    
    for (int c = 0; c < n - 1; c++){
        for (int r = 0; r < m; r++){
            int lo = 1, hi = m - r, candidateL = 0;
            while(lo <= hi){
                int mid = (lo + hi) / 2;
                if(query(r + 1, c + 1, r + mid, c + 2) == 0){
                    candidateL = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if(candidateL > bestL){
                bestL = candidateL;
                best_x = c;
                best_y = r;
            } else if(candidateL == bestL && candidateL > 0){
                if(c < best_x || (c == best_x && r < best_y)){
                    best_x = c;
                    best_y = r;
                }
            }
        }
    }

    if(bestL < 2) cout << "0 0 0\n";
    else cout << best_x + 1 << " " << m - best_y << " " << bestL << "\n";
    
    return 0;
}
