#include <iostream>
#include <string>

using namespace std;

string solve(const string& S, int K){
    const int N = S.size();
    if(N==1){
        if(K%2 == 0) return S;
        return std::string(1, 'A'+'B'-S[0]);
    }
    char top = '-';
    int shift = -1;
    for(int i=0;i<N-1;i++){
        top = (S[i] == "AB"[i%2] ? 'A' : 'B');
        if(i > 0){
            if(K == 1){
                shift = i;
                break;
            }
            --K;
        }
        if(top == 'A'){
            if(K == 1){
                top = 'B';
                shift = i;
                break;
            }
            --K;
        }
    }
    if(shift == -1){
        top = ((K%2 == 1 && S.size()%2 == 1) ? 'A' : 'B');
        shift = N;
    }
    string res = "";
    res += top;
    for(int i=1;i<N-1;i++){
        if(i+shift < N-1){
            if(shift%2 == 0) res += S[i+shift];
            else res += (S[i+shift] == 'A' ? "B" : "A");
        } else {
            if((N-1-i)%2 == 0) res += "A";
            else res += "B";
        }
    }
    res += "A";
    return res;
}

string naive(const string& S, int K){
    string res = S;
    for(int i=0;i<K;i++){
        int pos = 0, dir = 1;
        while(0 <= pos && pos < S.size()){
            if(res[pos] == 'A') dir = -dir;
            res[pos] = 'A' + 'B' - res[pos];
            pos += dir;
        }
    }
    return res;
}

string solve2(const string& S, int K){
    string res = naive(S, 1);
    if(K==1) return res;
    res = naive(res, 1);
    if(K==2) return res;
    return solve(res, K-2);
}


int main(){
    int N, K; cin >> N >> K;
    string S; cin >> S;
    cout << solve2(S, K) << endl;
}