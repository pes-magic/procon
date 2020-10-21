#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> solve(const vector<int>& A, const vector<int>& B){
    const int N = A.size();
    vector<int> res(N, -1);
    int last = -1;
    for(int i=0;i<N;i++){
        if(A[i] == B[i]){
            res[i] = 0;
            last = i;
        } else if(A[i] < B[i]){
            last = -1;
        } else if(last != -1){
            int L = last, R = i;
            while(R-L > 1){
                int mid = (L+R)/2;
                int dst = A[mid] + i - mid;
                if(dst <= B[i]) L = mid;
                else R = mid;
            }
            if(A[L]+i-L == B[i]){
                res[i] = i-L;
            }
        }
    }
    for(int i=N-1;i>0;i--){
        if(res[i] > 0 && res[i-1] < res[i]) res[i] = 1;
    }
    return res;
}

int main(){
    int N, L; cin >> N >> L;
    vector<int> A(N+2, 0), B(N+2, 0);
    for(int i=1;i<=N;i++) cin >> A[i];
    for(int i=1;i<=N;i++) cin >> B[i];
    A.back() = L+1;
    B.back() = L+1;
    vector<int> res(N+2, -1);
    auto v = solve(A, B);
    for(int i=0;i<N+2;i++) if(v[i] != -1) res[i] = v[i];
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    for(auto& t : A) t = L+1-t;
    for(auto& t : B) t = L+1-t;
    v = solve(A, B);
    for(int i=0;i<N+2;i++) if(v[i] != -1) res[N+1-i] = v[i];
    if(all_of(res.begin(), res.end(), [](int t){ return t != -1; })){
        cout << accumulate(res.begin(), res.end(), 0LL) << endl;
    } else {
        cout << -1 << endl;
    }
}