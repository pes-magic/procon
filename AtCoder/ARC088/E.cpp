#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

template<typename T>
class RangeAddQuery {
public:
    explicit RangeAddQuery(int n) : N(calcN_(n)) {
        mVal.assign(2*N+1, 0);
    }
    void update(int l, int r, T value){
        updateImpl_(l, r, value, 0, 0, N);
    }
    T get(int idx){
        int i = N + idx - 1;
        auto res = mVal[i];
        while(i > 0){
            i = (i-1)/2;
            res += mVal[i];
        }
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void updateImpl_(int l, int r, T value, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return;
        if(l <= rangeL && rangeR <= r){
            mVal[idx] += value;
        } else {
            int rangeM = (rangeL+rangeR)/2;
            updateImpl_(l, r, value, 2*idx+1, rangeL, rangeM);
            updateImpl_(l, r, value, 2*idx+2, rangeM, rangeR);
        }
    }
    const int N;
    vector<T> mVal;
};

long long solve(const string& S){
    const int n = S.size();
    RangeAddQuery<int> raq(n);
    vector<deque<int>> pos(26);
    for(int i=0;i<n;i++) pos[S[i]-'a'].push_back(i);
    if(count_if(pos.begin(), pos.end(), [](auto& v){ return v.size()%2 == 1; }) != n%2) return -1;
    long long res = 0;
    for(int i=0;i<n/2;i++){
        int minIdx = 0;
        int minCost = 1000000007;
        for(int j=0;j<pos.size();j++){
            if(pos[j].size() < 2) continue;
            int a = pos[j].front();
            int b = pos[j].back();
            int cost = abs(a + raq.get(a) - i) + abs(b + raq.get(b) - (n-i-1));
            if(cost < minCost){
                minCost = cost;
                minIdx = j;
            }
        }
        res += minCost;
        raq.update(0, pos[minIdx].front(), 1);
        raq.update(pos[minIdx].back(), n, -1);
        pos[minIdx].pop_front();
        pos[minIdx].pop_back();
    }
    for(auto& v : pos){
        if(!v.empty()) res += abs(v.front() + raq.get(v.front()) - n/2);
    }
    return res;
}

int main(){
    string S; cin >> S;
    cout << solve(S) << endl;
}
