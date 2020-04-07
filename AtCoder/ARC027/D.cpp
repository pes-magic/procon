#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

vector<vector<int>> mul(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    const int n = a.size();
    vector<vector<int>> res(n, vector<int>(n, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++) res[i][j] = (res[i][j] + (long long)a[i][k] * b[k][j]) % MOD;
        }
    }
    return res;
}

vector<int> mul(const vector<vector<int>>& a, const vector<int>& b) {
    const int n = a.size();
    vector<int> res(n, 0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) res[i] = (res[i] + (long long)a[i][j] * b[j]) % MOD;
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<vector<int>> ident(10, vector<int>(10, 0));
        vector<vector<vector<int>>> a(N, vector<vector<int>>(10, vector<int>(10, 0)));
        for(int i=0;i<10;i++) ident[i][i] = 1;
        for(auto& m : a){
            int h; cin >> h;
            for(int i=0;i<h;i++) m[0][i] = 1;
            for(int i=0;i<9;i++) m[i+1][i] = 1;
        }
        int block = 0;
        while(block * block < N) ++block;
        vector<vector<vector<int>>> d((N+block-1)/block, ident);
        for(int i=0;i<a.size();i++){
            for(int j=i*block;j<min(N,(i+1)*block);j++){
                d[i] = mul(d[i], a[j]);
            }
        }
        int Q; cin >> Q;
        for(int i=0;i<Q;i++){
            int s, t; cin >> s >> t;
            --s; --t;
            vector<int> m(10, 0);
            m[0] = 1;
            int e1 = t/block*block;
            for(int j=t-1;j>=max(e1, s);j--) m = mul(a[j], m);
            while(e1-block>=s){
                e1 -= block;
                m = mul(d[e1/block], m);
            }
            for(int j=e1-1;j>=s;j--) m = mul(a[j], m);
            cout << m[0] << endl;
        }
    }
}