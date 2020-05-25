#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

int main(){
    string S; cin >> S;
    vector<long long> res(S.size()+1, 0);
    for(int i=0;i<S.size();i++){
        if(S[i] == '<') res[i+1] = max(res[i+1], res[i]+1);
    }
    for(int i=S.size();i>0;i--){
        if(S[i-1] == '>') res[i-1] = max(res[i-1], res[i]+1);
    }
    cout << accumulate(res.begin(), res.end(), 0LL) << endl;
}