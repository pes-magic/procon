#include <iostream>
#include <map>
#include <cmath>
#include <queue>

using namespace std;

int main(){
    int T; cin >> T;
    while(T--){
        long long N, A, B, C, D; cin >> N >> A >> B >> C >> D;
        map<long long, long long> mp;
        mp[0] = 0;
        priority_queue<pair<long long, long long>> qu;
        qu.emplace(0, N);
        long long res = 1LL << 60;
        while(!qu.empty()){
            auto p = qu.top(); qu.pop();
            auto cur = -p.first;
            if(cur >= res) break;
            auto v = p.second;
            if(v <= 2000000000){
                res = min(res, cur + v * D);
            }
            auto check = [&](long long cost, long long value){
                if(!mp.count(value) || mp[value] > cost){
                    mp[value] = cost;
                    qu.emplace(-cost, value);
                }
            };
            for(int i=-1;i<=1;i++){
                if(v+i > 0 && (v+i)%2 == 0){
                    check(cur+abs(i)*D+A, (v+i)/2);
                }
            }
            for(int i=-2;i<=2;i++){
                if(v+i > 0 && (v+i)%3 == 0){
                    check(cur+abs(i)*D+B, (v+i)/3);
                }
            }
            for(int i=-4;i<=4;i++){
                if(v+i == 0){
                    check(cur+abs(i)*D, v+i);
                }
                if(v+i > 0 && (v+i)%5 == 0){
                    check(cur+abs(i)*D+C, (v+i)/5);
                }
            }
        }
        cout << res << endl;
    }
}