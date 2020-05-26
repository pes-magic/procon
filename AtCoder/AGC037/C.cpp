#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> A(N), B(N);
    for(auto& t : A) cin >> t;
    for(auto& t : B) cin >> t;
    priority_queue<pair<int, int>> qu;
    for(int i=0;i<N;i++) qu.emplace(B[i], i);
    long long res = 0;
    while(!qu.empty()){
        int idx = qu.top().second; qu.pop();
        if(A[idx] == B[idx]) continue;
        int a = B[(idx+N-1)%N], b = B[(idx+1)%N];
        if(max(a, b) <= A[idx]){
            if((B[idx]-A[idx])%(a+b) != 0) break;
            res += (B[idx]-A[idx])/(a+b);
            B[idx] = A[idx];
        } else {
            long long m = max(1, (B[idx] - max(a, b))/(a+b));
            res += m;
            B[idx] -= m * (a + b);
            if(B[idx] >= max(a, b)){
                res++;
                B[idx] -= a + b;
            }
            if(B[idx] < A[idx]) break;
            if(B[idx] > A[idx]) qu.emplace(B[idx], idx);
        }
    }
    cout << (A == B ? res : -1) << endl;
}