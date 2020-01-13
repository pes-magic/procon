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
    string S;
    while(cin >> S){
        vector<vector<int>> zlen;
        const int N = S.size();
        long long res = 0;
        for(int i=0;i<N;i++) zlen.push_back(Zalgorithm(S.substr(i)));
        for(int p2=1;p2<N;p2++){
            for(int p6=zlen[p2].size()-1;p6>0;p6--){
                if(zlen[p2][p6] != zlen[p2].size() - p6) continue;
                int p3 = p2 + zlen[p2].size() - p6;
                if(p3 >= p2 + p6) continue;
                for(int p4=1;p4<zlen[p3].size();p4++){
                    if(zlen[p3][p4] >= p4){
                        int p5 = p3 + 2 * p4;
                        if(p5 < p2 + p6) ++res;
                    }
                }
            }
        }
        cout << res << endl;
    }
}