#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> convert(const string& S){
    vector<int> sum(S.size()+1, 0);
    for(int i=0;i<S.size();i++){
        sum[i+1] = sum[i] + (S[i]-'A'+1);
    }
    return sum;
}

int main(){
    string S, T; cin >> S >> T;
    auto s = convert(S);
    auto t = convert(T);
    int Q; cin >> Q;
    for(int i=0;i<Q;i++){
        int a, b, c, d; cin >> a >> b >> c >> d;
        cout << ((s[b]-s[a-1])%3 == (t[d]-t[c-1])%3 ? "YES" : "NO") << endl;
    }
}