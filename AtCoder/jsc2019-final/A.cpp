#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<int> A(N), B(M);
    for(auto& t : A) cin >> t;
    for(auto& t : B) cin >> t;
    vector<pair<int, int>> vp(2000001, make_pair(-1, -1));
    bool find = false;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            auto& p = vp[A[i]+B[j]];
            if(p.first == -1){
                p = make_pair(i, j);
            } else if(!find) {
                cout << p.first << " " << p.second << " " << i << " " << j << endl;
                find = true;
            }
        }
        if(find) break;
    }
    if(!find) cout << -1 << endl;
}