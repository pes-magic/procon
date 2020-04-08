#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> x(N);
        for(auto& t : x) cin >> t;
        int L; cin >> L;
        vector<int> next(N, 0);
        int dst = 0;
        for(int i=0;i<N;i++){
            while(dst != N-1 && x[i] + L >= x[dst+1]) ++dst;
            next[i] = dst;
        }
        vector<vector<int>> step;
        step.push_back(next);
        while(true){
            if(step.back().front() == N-1) break;
            for(int i=0;i<N;i++) next[i] = step.back()[step.back()[i]];
            step.push_back(next);
        }
        int Q; cin >> Q;
        for(int i=0;i<Q;i++){
            int a, b; cin >> a >> b;
            --a; --b;
            if(a > b) swap(a, b);
            int res = 1;
            for(int j=step.size()-1;j>=0;j--){
                if(step[j][a] < b){
                    a = step[j][a];
                    res += 1 << j;
                }
            }
            cout << res << endl;
        }
    }
}