#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    int N, K; cin >> N >> K;
    string S; cin >> S;
    string T = S;
    reverse(T.begin(), T.end());
    S += T;
    char minC = '~';
    int maxRep = 1;
    string minSuffix = "";
    for(int i=0;i<N;i++){
        if(S[i] > minC) continue;
        if(S[i] < minC){
            minC = S[i];
            maxRep = 0;
            minSuffix = "~";
        }
        int len = 0;
        for(int j=i;j<N+i;j++){
            if(minC == S[j]) ++len;
            else break;
        }
        int repLen = len;
        for(int j=1;j<K;j++){
            repLen *= 2;
            if(repLen >= N){
                repLen = N;
                break;
            }
        }
        string curSuffix = "";
        for(int j=i+len;j<N+i;j++){
            if(repLen + curSuffix.size() == N) break;
            curSuffix += S[j];
        }
        if(maxRep < repLen || maxRep == repLen && minSuffix > curSuffix){
            maxRep = repLen;
            minSuffix = curSuffix;
        }
    }
    cout << string(maxRep, minC) << minSuffix << endl;
}