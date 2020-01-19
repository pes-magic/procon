#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        long long res = 0;
        vector<int> visit(N, 0);
        for(int back=1;back<=N-2;back++){
            int a = N-1;
            int b = 0;
            int idx=1;
            long long cur = 0;
            while(true){
                a -= back;
                if(a <= back) break;
                if(a <= 0 || visit[a]) break;
                visit[a] = 1;
                b += back;
                if(b >= N-1 || visit[b]) break;
                visit[b] = 1;
                cur += A[a] + A[b];
                res = max(cur, res);
                ++idx;
            }
            a = N-1; b = 0;
            for(int i=0;i<idx;i++){
                a -= back; b += back;
                if(a >= 0) visit[a] = 0;
                if(b < N) visit[b] = 0;
            }
        }
        cout << res << endl;
    }
}