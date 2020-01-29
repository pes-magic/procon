#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int check(const vector<vector<int>>& M, const vector<int>& ng){
    const int N = M.size();
    vector<int> in(N, 0);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) if(M[i][j]) in[j]++;
    }
    queue<int> qu;
    for(int i=0;i<N;i++){
        if(!ng[i] && !in[i]) qu.push(i);
    }
    int res = 0;
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        ++res;
        for(int i=0;i<N;i++){
            if(M[p][i]){
                --in[i];
                if(!in[i] && !ng[i]) qu.push(i);
            }
        }
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        int A; cin >> A;
        vector<int> x(A), y(A);
        for(int i=0;i<A;i++){
            cin >> x[i] >> y[i];
            --x[i]; --y[i];
        }
        int B; cin >> B;
        vector<int> u(B), v(B);
        for(int i=0;i<B;i++){
            cin >> u[i] >> v[i];
            --u[i]; --v[i];
        }
        int res = 0;
        for(int i=0;i<(1<<B);i++){
            vector<vector<int>> M(N, vector<int>(N, 0));
            vector<int> ng(N, 0);
            for(int j=0;j<A;j++){
                M[y[j]][x[j]] = 1;
            }
            for(int j=0;j<B;j++){
                if(i&(1<<j)) M[u[j]][v[j]] = 1;
                else ng[u[j]] = 1;
            }
            res = max(res, check(M, ng));
        }
        cout << res << endl;
    }
}