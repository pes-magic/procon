#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<long long> A(N);
        long long all = 0;
        for(auto& t : A){
            cin >> t;
            all ^= t;
        }
        int start = 0;
        for(int i=60;i>=0;i--){
            if(all&(1LL<<i)) continue;
            int idx = -1;
            for(int j=start;j<N;j++){
                if(A[j]&(1LL<<i)){
                    idx = j;
                    break;
                }
            }
            if(idx == -1) continue;
            swap(A[start], A[idx]);
            for(int j=0;j<N;j++){
                if(j != start && (A[j]&(1LL<<i))) A[j] ^= A[start];
            }
            ++start;
        }
        long long cur = 0;
        for(int i=0;i<start;i++) cur ^= A[i];
        cout << (2*(cur&~all) + all) << endl;
    }
}