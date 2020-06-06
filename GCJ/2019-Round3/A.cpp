#include <iostream>
#include <vector>

using namespace std;

const long long M = 10000000000LL;

void action(long long p, vector<pair<long long, long long>>& interval){
    for(int i=0;i<interval.size();i++){
        if(interval[i].first <= p && p < interval[i].second){
            auto b = interval[i].first;
            auto e = interval[i].second;
            swap(interval[i], interval.back());
            interval.pop_back();
            if(p - b >= M) interval.emplace_back(b, p);
            p += M;
            if(e - p >= M) interval.emplace_back(p, e);
            break;
        }
    }
}

long long decideMove(const vector<pair<long long, long long>>& interval){
    for(auto& p : interval){
        if(p.second - p.first >= 3*M) return p.first + 2*M;
    }
    for(auto& p : interval){
        if(p.second - p.first > 2*M) return p.first + M - 1;
    }
    for(auto& p : interval){
        if(p.second - p.first == 2*M){
            return p.first + interval.size()%2;
        }
    }
    return interval[0].first;
}

bool solve(){
    vector<pair<long long, long long>> interval;
    interval.emplace_back(1, 100*M+1);
    while(true){
        long long p; cin >> p;
        if(p < 0) return p != -1;
        action(p, interval);
        p = decideMove(interval);
        action(p, interval);
        cout << p << endl;
    }
}

int main(){
    int T, W; cin >> T >> W;
    for(int _=0;_<T;_++){
        if(!solve()) break;;
    }
}