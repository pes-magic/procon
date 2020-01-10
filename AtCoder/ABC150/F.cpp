#include <iostream>
#include <vector>

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
        vector<int> a(N), b(N);
        for(auto& t : a) cin >> t;
        for(auto& t : b) cin >> t;
        vector<int> xa(N), xb(N);
        for(int i=0;i<N;i++){
            xa[i] = a[i]^a[(i+1)%N];
            xb[i] = b[i]^b[(i+1)%N];
        }
        vector<int> z = xb;
        z.insert(z.end(), xa.begin(), xa.end());
        z.insert(z.end(), xa.begin(), xa.end());
        auto len = Zalgorithm(z);
        for(int i=0;i<N;i++){
            if(len[N+i] >= N) cout << i << " " << (a[i]^b[0]) << endl;
        }
    }
}