#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<vector<int>> A(N, vector<int>(N-1));
        for(auto& v : A){
            for(auto& t : v){
                cin >> t; --t;
            }
        }
        vector<int> day(N, 0);
        vector<int> idx(N, 0);
        queue<pair<int, int>> qu;
        for(int i=0;i<N;i++){
            if(i < A[i][0] && A[A[i][0]][0] == i){
                qu.emplace(i, A[i][0]);
                idx[i] = 1;
                idx[A[i][0]] = 1;
            }
        }
        int battle = 0;
        while(!qu.empty()){
            auto p = qu.front(); qu.pop();
            ++battle;
            int d = max(day[p.first], day[p.second]) + 1;
            day[p.first] = day[p.second] = d;
            auto check = [&](int t){
                if(idx[t] < N-1){
                    int next = A[t][idx[t]];
                    if(idx[next] < N-1 && A[next][idx[next]] == t){
                        qu.emplace(t, next);
                        ++idx[t];
                        ++idx[next];
                    }
                }
            };
            check(p.first);
            check(p.second);
        }
        if(battle < N*(N-1)/2){
            cout << -1 << endl;
        } else {
            cout << *max_element(day.begin(), day.end()) << endl;
        }
    }
}