#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, K, S;
    while(cin >> N >> K >> S){
        vector<int> res;
        for(int i=0;i<K;i++) res.push_back(S);
        for(int i=K;i<N;i++) res.push_back(S == 1000000000 ? 1 : S+1);
        cout << res[0];
        for(int i=1;i<N;i++) cout << " " << res[i];
        cout << endl;
    }
}