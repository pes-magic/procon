#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<pair<int, int>> solve(int N){
    int start = 0;
    while(start + (1 << start) <= N) ++start;
    vector<int> use(start, 0);
    use[0] = use[start-1] = 1;
    int sum = (start-1) + (1 << (start-1));
    for(int i=start-2;i>=0;i--){
        if(sum + (1 << i) - 1 <= N){
            use[i] = 1;
            sum += (1 << i) - 1;
        }
    }
    vector<pair<int, int>> res;
    res.emplace_back(1, 1);
    sum = 1;
    bool f = true;
    for(int i=1;i<start;i++){
        if(!use[i]){
            res.emplace_back(i+1, f ? 1 : i+1);
            sum += 1;
        } else {
            if(f){
                for(int j=1;j<=i+1;j++) res.emplace_back(i+1, j);
            } else {
                for(int j=i+1;j>=1;j--) res.emplace_back(i+1, j);
            }
            f = !f;
            sum += (1 << i);
        }
    }
    while(sum < N){
        ++start;
        res.emplace_back(start, f ? 1 : start);
        ++sum;
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N; cin >> N;
        auto res = solve(N);
        printf("Case #%d:\n", t);
        for(auto& p : res) cout << p.first << " " << p.second << endl;
    }
}