#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    int N, K;
    while(cin >> N >> K){
        string S; cin >> S;
        vector<string> vs;
        string T = S;
        reverse(T.begin(), T.end());
        S += T;
        char best = 'z' + 1;
        int len = 0;
        int rep = 0;
        for(int i=0;i<N;i++){
            int curL = 0;
            for(int j=i;j<S.size();j++){
                if(S[i] == S[j]) ++curL;
                else break;
            }
            if(S[i] < best || (S[i] == best && curL > len)){
                vs.clear();
                best = S[i];
                len = curL;
                rep = len;
                for(int j=0;j<K-1 && rep < N;j++) rep *= 2;
                rep = min(N, rep);
            }
            if(S[i] == best && len == curL){
                vs.emplace_back(S.substr(i+len, N-rep));
            }
        }
        sort(vs.begin(), vs.end());
        cout << (string(rep, best) + vs[0]) << endl;
    }
}