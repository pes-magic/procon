#include <iostream>
#include <queue>

using namespace std;

int main(){
    int N, M;
    while(cin >> N >> M){
        priority_queue<int> qu;
        for(int i=0;i<N;i++){
            int A; cin >> A;
            qu.push(A);
        }
        for(int i=0;i<M;i++){
            int t = qu.top(); qu.pop();
            qu.push(t/2);
        }
        long long res = 0;
        while(!qu.empty()){
            res += qu.top();
            qu.pop();
        }
        cout << res << endl;
    }
}