#include <iostream>
#include <vector>
#include <atcoder/twosat>

using namespace std;

int main(){
    int N, D; cin >> N >> D;
    vector<int> p(2*N);
    for(auto& t : p) cin >> t;
    atcoder::two_sat ts(N);
    for(int i=0;i<2*N;i++){
        for(int j=2*(i/2+1);j<2*N;j++){
            if(abs(p[i]-p[j]) >= D) continue;
            ts.add_clause(i/2, !(i%2), j/2, !(j%2));
        }
    }
    if(ts.satisfiable()){
        cout << "Yes" << endl;
        auto b = ts.answer();
        for(int i=0;i<N;i++) cout << p[2*i+b[i]] << endl;
    } else {
        cout << "No" << endl;
    }
}