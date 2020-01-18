#include <iostream>
#include <vector>

using namespace std;

int bitCount(int m){
    int res = 0;
    for(int t=m;t;t&=t-1) res++;
    return res;
}

int solve(const vector<int>& A, const vector<int>& B){
    int N = A.size();
    int res = 1000000;
    vector<pair<int, int>> v(N);
    for(int m=0;m<(1<<N);m++){
        if(bitCount(m)%2 == 1) continue;
        for(int i=0;i<N;i++) v[i] = make_pair(((m>>i)%2)?B[i]:A[i], i);
        int cnt = 0;
        bool valid = true;
        for(int i=0;i<N;i++){
            int mVal = 100;
            for(int j=i;j<N;j++){
                mVal = min(mVal, v[j].first);
            }
            bool ok = false;
            for(int j=i;j<N;j++){
                if(v[j].first != mVal) continue;
                int d = (v[j].second - i + 10000) % 2;
                if(d != (m>>v[j].second)%2) continue;
                for(int k=j-1;k>=i;k--){
                    swap(v[k], v[k+1]); 
                    ++cnt;
                }
                ok = true;
                break;
            }
            if(!ok){ valid = false; break; }
        }
        if(valid){
            res = min(res, cnt); }
    }
    return res < 1000000 ? res : -1;
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