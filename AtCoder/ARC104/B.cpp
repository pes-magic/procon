#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N; cin >> N;
    string S; cin >> S;
    int res = 0;
    for(int i=0;i<N;i++){
        vector<int> cnt(256, 0);
        for(int j=i;j<N;j++){
            cnt[S[j]]++;
            if(cnt['A']==cnt['T'] && cnt['C']==cnt['G']) ++res;
        }
    }
    cout << res << endl;
}