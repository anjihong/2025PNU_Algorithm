#include <bits/stdc++.h>

using namespace std;

int length = 0, x = 5001, y = 5001;
 
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    
    int N, M; cin >> N >> M;
    vector<string> rows(N);
    for (int i = 0; i < N; i++) cin >> rows[i];

    vector<string> grid(N);
    for (int i = 0; i < N; i++) grid[i] = rows[N - 1 - i];
    
    
    for (int i = 1; i < N; i++){
        int j = 0;
        while(j < M){
            if(grid[i][j]=='0' && grid[i-1][j]=='0'){
                int start = j;
                while(j < M && grid[i][j]=='0' && grid[i-1][j]=='0')
                    j++;
                int cl = j - start;
                int cx = start + 1;
                int cy = i + 1;
                if(cl > length || (cl == length && (cx < x || (cx == x && cy < y)))){
                    length = cl;
                    x = cx;
                    y = cy;
                }
            } else {
                j++;
            }
        }
    }
    
    for (int j = 0; j < M - 1; j++){
        int i = 0;
        while(i < N){
            if(grid[i][j]=='0' && grid[i][j+1]=='0'){
                int start = i;
                while(i < N && grid[i][j]=='0' && grid[i][j+1]=='0')
                    i++;
                int cl = i - start;
                int cx = j + 1;
                int cy = i;
                if(cl > length || (cl == length && (cx < x || (cx == x && cy < y)))){
                    length = cl;
                    x = cx;
                    y = cy;
                }
            } else {
                i++;
            }
        }
    }
    
    if(length < 2)
        cout << "0 0 0";
    else
        cout << x << " " << y << " " << length;
    
    return 0;
}
