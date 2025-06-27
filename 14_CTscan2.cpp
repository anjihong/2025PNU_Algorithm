#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> rowT, colT, diagDR, diagDL;
vector<int> R, C, D1, D2;
int G[10][10];

void dfs(int p){
    cout << p << '\n';
    if(p==N*N){
        for(int d=0; d<2*N-1; d++)
            if(D1[d]!=diagDL[d] || D2[d]!=diagDR[d]) return;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cout<<(G[i][j]?'B':'-');
                if(j+1<N) cout<<' ';
            }
            cout<<"\n";
        }
        exit(0);
    }
    int i=p/N, j=p%N;
    int d1=i+j, d2=i-j+N-1;
    for(int v=0;v<2;v++){
        int bR=R[i], bC=C[j], b1=D1[d1], b2=D2[d2];
        if(v){
            R[i]++; C[j]++; D1[d1]++; D2[d2]++;
        }
        bool ok = R[i]<=rowT[i] && C[j]<=colT[j]
               && D1[d1]<=diagDL[d1] && D2[d2]<=diagDR[d2]
               && (j<N-1 || R[i]==rowT[i])
               && (i<N-1 || C[j]==colT[j]);
        if(ok){
            G[i][j]=v;
            dfs(p+1);
        }
        R[i]=bR; C[j]=bC; D1[d1]=b1; D2[d2]=b2;
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin>>N;
    colT.resize(N); rowT.resize(N);
    for(int &x:colT) cin>>x;      // ↓ 방향: 각 열의 B 개수
    for(int &x:rowT) cin>>x;      // → 방향: 각 행의 B 개수
    diagDR.resize(2*N-1);         // ↘ 방향
    diagDL.resize(2*N-1);         // ↙ 방향
    for(int &x:diagDR) cin>>x;
    for(int &x:diagDL) cin>>x;

    R.assign(N,0); C.assign(N,0);
    D1.assign(2*N-1,0); D2.assign(2*N-1,0);
    dfs(0);
    return 0;
}
