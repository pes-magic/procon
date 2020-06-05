#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long solve(const vector<int>& low, const vector<int>& high){
    long long res = 0;
    int pos = 0;
    long long sum = 0;
    for(int i=0;i<low.size();i++){
        if(low[i] >= pos) break;
        sum += pos - low[i];
        pos = low[i];
        res = max(res, sum + abs(pos));
        if(high[i] <= pos) break;
        sum += high[i] - pos;
        pos = high[i];
        res = max(res, sum + abs(pos));
    }
    sum = 0;
    pos = 0;
    for(int i=0;i<low.size();i++){
        if(high[i] <= pos) break;
        sum += high[i] - pos;
        pos = high[i];
        res = max(res, sum + abs(pos));
        if(low[i] >= pos) break;
        sum += pos - low[i];
        pos = low[i];
        res = max(res, sum + abs(pos));
    }
    return res;
}

int main(){
    int N; cin >> N;
    vector<int> L(N), R(N);
    for(int i=0;i<N;i++) cin >> L[i] >> R[i];
    sort(L.rbegin(), L.rend());
    sort(R.begin(), R.end());
    cout << solve(R, L) << endl;
}