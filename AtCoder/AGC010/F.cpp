#include <iostream>
#include <vector>

using namespace std;

bool search(const vector<vector<int>>& g, const vector<int>& A, int pos, int prev){
    for(auto& t : g[pos]){
        if(t == prev) continue;
        if(A[t] >= A[pos]) continue;
        if(!search(g, A, t, pos)) return true;
    }
    return false;
}

int main(){
    int N; cin >> N;
    vector<int> A(N);
    for(auto& t : A) cin >> t;
    vector<vector<int>> g(N);
    for(int i=0;i<N-1;i++){
        int a, b; cin >> a >> b;
        g[a-1].push_back(b-1);
        g[b-1].push_back(a-1);
    }
    for(int i=0;i<N;i++) if(search(g, A, i, -1)) cout << i+1 << " ";
    cout << endl;
}