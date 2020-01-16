#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N = 0;
    while(cin >> N){
        vector<string> vs(N);
        for(auto& s : vs) cin >> s;
        int res = 0;
        for(int s=0;s<N;s++){
            bool ok = true;
            for(int j=0;j<N;j++){
                for(int k=j+1;k<N;k++){
                    if(vs[(j+s)%N][k] != vs[(k+s)%N][j]) ok = false;
                }
            }
            if(ok) res += N;
        }
        cout << res << endl;
    }
}