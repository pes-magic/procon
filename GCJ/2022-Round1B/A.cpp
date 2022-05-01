#include <iostream>
#include <deque>

using namespace std;

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N; cin >> N;
        deque<int> qu;
        for(int i=0;i<N;i++){
            int a; cin >> a;
            qu.push_back(a);
        }
        int cur = -100;
        int res = 0;
        for(int i=0;i<N;i++){
            int a = qu.front();
            int b = qu.back();
            if(a < b){
                if(a >= cur){
                    cur = a;
                    ++res;
                }
                qu.pop_front();
            } else {
                if(b >= cur){
                    cur = b;
                    ++res;
                }
                qu.pop_back();
            }
        }
        cout << "Case #" << t << ": " << res << endl;
    }
}