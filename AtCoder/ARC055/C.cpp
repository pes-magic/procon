#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> Zalgorithm(auto S){
    vector<int> res(S.size());
    res[0] = S.size();
    int i = 1, j = 0;
    while (i < S.size()) {
        while (i+j < S.size() && S[j] == S[i+j]) ++j;
        res[i] = j;
        if (j == 0) { ++i; continue;}
        int k = 1;
        while (i+k < S.size() && k+res[k] < j) res[i+k] = res[k], ++k;
        i += k; j -= k;
    }
    return res;
}

long long solve(const string& S){
    const int N = S.size();
    auto R = S;
    reverse(R.begin(), R.end());
    auto zs = Zalgorithm(S);
    auto zr = Zalgorithm(R);
    long long res = 0;
    for(int i=N/2+1;i<N;i++){
        if(!zs[i]) continue;
        int lower = max(1, N-i-zs[i]);
        res += max(0, min(N-i-1, zr[N-i])-lower+1);
    }
    return res;
}

int main(){
    string S;
    while(cin >> S){
        cout << solve(S) << endl;
    }
}