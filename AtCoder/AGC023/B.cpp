#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N; cin >> N;
    vector<string> vs(N);
    for(auto& s : vs) cin >> s;
    int res = 0;
    for(int i=0;i<N;i++){
        bool ok = true;
        for(int j=0;j<N;j++){
            for(int k=j+1;k<N;k++){
                int b = (k+i)%N;
                if(vs[j][(k+i)%N] != vs[k][(j+i)%N]) ok = false;
            }
        }
        if(ok) res += N;
    }
    cout << res << endl;
}