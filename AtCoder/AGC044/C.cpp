#include <iostream>
#include <vector>
#include <string>

using namespace std;

pair<vector<int>, vector<int>> solve(int N, const string& T){
    if(N==0){
        return make_pair(vector<int>(1, 0), vector<int>(T.size(), 0));
    }
    auto prev = solve(N-1, T);
    auto& P = prev.first;
    auto& W = prev.second;
    vector<int> D(3*P.size());
    for(int i=0;i<D.size();i++) D[i] = i/P.size();
    int salsa = 0;
    vector<int> lastSalsa(3*P.size(), 0);
    vector<int> curW(W.size());
    for(int i=0;i<T.size();i++){
        for(int j=W[i];j<D.size();j+=P.size()){
            if(salsa != lastSalsa[j]) D[j] = (3-D[j])%3;
            lastSalsa[j] = salsa;
            if(D[j] == 2) curW[i] = j;
        }
        if(T[i] == 'S'){
            salsa = 1 - salsa;
        } else {
            for(int j=W[i];j<=D.size();j+=P.size()) D[j] = (D[j]+1)%3;
        }
    }
    vector<int> curP(D.size());
    for(int i=0;i<curP.size();i++){
        if(salsa != lastSalsa[i]) D[i] = (3-D[i])%3;
        curP[i] = P.size() * D[i] + P[i%P.size()];
    }
    return make_pair(curP, curW);
}

int main(){
    int N; cin >> N;
    string T; cin >> T;
    auto res = solve(N, T).first;
    cout << res[0];
    for(int i=1;i<res.size();i++) cout << " " << res[i];
    cout << endl;
}