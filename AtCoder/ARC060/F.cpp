#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

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
    string S;
    while(cin >> S){
        vector<int> z = Zalgorithm(S);
        int cycle = S.size();
        for(int i=1;i<S.size();i++){
            if(S.size()%i) continue;
            bool ok = true;
            for(int j=i;j<S.size();j+=i) if(z[j] != S.size() - j) ok = false;
            if(ok){
                cycle = i;
                break;
            }
        }
        if(cycle == 1 || cycle == S.size()){
            cout << S.size()/cycle << endl;
            cout << 1 << endl;
            continue;
        }
        cout << 2 << endl;
        vector<int> valid(S.size(), 1);
        valid[0] = 0;
        for(int i=1;i<S.size();i++){
            for(int j=2*i;j<S.size();j+=i){
                if(i + z[i] >= j) valid[j] = 0;
            }
        }
        auto T = S;
        reverse(T.begin(), T.end());
        vector<int> zr = Zalgorithm(T);
        for(int i=1;i<T.size();i++){
            for(int j=2*i;j<S.size();j+=i){
                if(i + zr[i] >= j) valid[S.size()-j] = 0;
            }
        }
        cout << accumulate(valid.begin(), valid.end(), 0) << endl;
    }
}