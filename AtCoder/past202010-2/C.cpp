#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<string> a(N);
    for(auto& s : a) cin >> s;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            int cnt = 0;
            for(int dx=-1;dx<=1;dx++){
                for(int dy=-1;dy<=1;dy++){
                    int ni = i+dx;
                    int nj = j+dy;
                    if(0 <= ni && ni < N && 0 <= nj && nj < M && a[ni][nj] == '#') cnt++;
                }
            }
            cout << cnt;
        }
        cout << endl;
    }
}