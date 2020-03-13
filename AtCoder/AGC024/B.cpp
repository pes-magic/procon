#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> pos(N);
        for(int i=0;i<N;i++){
            int t; cin >> t;
            pos[t-1] = i;
        }
        int res = 0;
        int len = 0;
        int pre = -1;
        for(auto& t : pos){
            if(t < pre) len = 1;
            else ++len;
            res = max(res, len);
            pre = t;
        }
        cout << N - res << endl;
    }
}