#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N, K, C;
    while(cin >> N >> K >> C){
        string S; cin >> S;
        vector<int> back(N+C+2, 0);
        int best = 0;
        for(int i=N-1;i>=0;i--){
            int add = back[i+C+1];
            back[i] = max(best, add + (S[i] == 'o' ? 1 : 0));
            best = max(back[i], best);
        }
        best = 0;
        int idx = -C;
        vector<int> front(N, 0);
        for(int i=0;i<N;i++){
            if(S[i] == 'o'){
                if(best + back[max(idx+C+1, i+1)] < K) cout << i+1 << endl;
            }
            int add = (i-C-1 >= 0 ? front[i-C-1] : 0);
            front[i] = max(best, add + (S[i] == 'o' ? 1 : 0));
            if(front[i] > best){
                best = front[i];
                idx = i;
            }
        }
    }
}