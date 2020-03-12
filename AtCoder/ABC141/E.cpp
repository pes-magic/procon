#include <iostream>
#include <vector>
#include <string>

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

int main(){
    int N;
    while(cin >> N){
        string S; cin >> S;
        int res = 0;
        for(int i=0;i<N;i++){
            auto v = Zalgorithm(S.substr(i));
            for(int j=1;j<v.size();j++){
                res = max(res, min(j, v[j]));
            }
        }
        cout << res << endl;
    }
}