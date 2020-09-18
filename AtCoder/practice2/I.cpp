#include <iostream>
#include <vector>
#include <string>
#include <atcoder/string>

using namespace std;

int main(){
    string S; cin >> S;
    const int N = S.size();
    auto sa = atcoder::suffix_array(S);
    auto lcp = atcoder::lcp_array(S, sa);
    long long res = N - sa[0];
    for(int i=0;i<N-1;i++) res += N - sa[i+1] - lcp[i];
    cout << res << endl;
}