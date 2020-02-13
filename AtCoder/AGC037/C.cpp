#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long solve(vector<int> A, vector<int> B){
    const int N = A.size();
    long long res = 0;
    priority_queue<pair<int,int>> qu;
    for(int i=0;i<N;i++){
        if(A[i] > B[i]) return -1;
        if(A[i] == B[i]) continue;
        qu.emplace(B[i], i);
    }
    while(!qu.empty()){
        int idx = qu.top().second; qu.pop();
        int sub = B[(idx+1)%N] + B[(idx+N-1)%N];
        int target = max(A[idx], max(B[(idx+1)%N], B[(idx+N-1)%N]));
        int num = max(1, (B[idx]-target)/sub);
        B[idx] -= num * sub;
        res += num;
        if(B[idx] < A[idx]) return -1;
        if(B[idx] > A[idx]) qu.emplace(B[idx], idx);
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N), B(N);
        for(auto& t : A) cin >> t;
        for(auto& t : B) cin >> t;
        cout << solve(A, B) << endl;
    }
}