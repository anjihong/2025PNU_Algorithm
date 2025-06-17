#include <bits/stdc++.h>
using namespace std;

vector <int> ans = {0,0,0};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;

    vector<string> inputRows(N);
    for (int i = 0; i < N; i++){
        cin >> inputRows[i];
    }

    vector<string> grid(N+1);
    for (int y = 1; y <= N; y++){
        grid[y] = inputRows[N - y];
    }
    
    
    for (int y = 2; y <= N; y++){
        int cnt = 0;
        int segStart = 1; 
        for (int x = 1; x <= M; x++){
            if ( grid[y][x-1]=='0' && grid[y-1][x-1]=='0' ){
                if(cnt == 0)
                    segStart = x;
                cnt++;
            } else {
                if(cnt > 0){
                    int L = cnt;
                    if(L > ans[2]){
                        ans[0] = segStart;
                        ans[1] = y;
                        ans[2] = L;
                    } else if(L == ans[2]){
                        if(segStart < ans[0] || (segStart == ans[0] && y < ans[1])){
                            ans[0] = segStart;
                            ans[1] = y;
                        }
                    }
                }
                cnt = 0;
            }
        }

        if(cnt > 0){
            int L = cnt;
            if(L > ans[2]){
                ans[2] = L;
                ans[0] = segStart;
                ans[1] = y;
            } else if(L == ans[2]){
                if(segStart < ans[0] || (segStart == ans[0] && y < ans[1])){
                    ans[0] = segStart;
                    ans[1] = y;
                }
            }
        }
    }
    
    for (int x = 1; x <= M-1; x++){
        int cnt = 0;
        int segStart = 1; 
        for (int y = 1; y <= N; y++){
            if ( grid[y][x-1]=='0' && grid[y][x]=='0' ){
                if(cnt == 0)
                    segStart = y;
                cnt++;
            } else {
                if(cnt > 0){
                    int L = cnt;
                    int candidateY = y - 1; 
                    int candidateX = x;    
                    if(L > ans[2]){
                        ans[2] = L;
                        ans[0] = candidateX;
                        ans[1] = candidateY;
                    } else if(L == ans[2]){
                        if(candidateX < ans[0] || (candidateX == ans[0] && candidateY < ans[1])){
                            ans[0] = candidateX;
                            ans[1] = candidateY;
                        }
                    }
                }
                cnt = 0;
            }
        }
        if(cnt > 0){
            int L = cnt;
            int candidateY = N; 
            int candidateX = x;
            if(L > ans[2]){
                ans[2] = L;
                ans[0] = candidateX;
                ans[1] = candidateY;
            } else if(L == ans[2]){
                if(candidateX < ans[0] || (candidateX == ans[0] && candidateY < ans[1])){
                    ans[0] = candidateX;
                    ans[1] = candidateY;
                }
            }
        }
    }
    
    if(ans[2] == 0){
        cout << "0 0 0";
    } else {
        cout << ans[0] << " " << ans[1] << " " << ans[2];
    }
    
    return 0;
}
