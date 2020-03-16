#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> generate(int n){
    if(n == 0) return vector<vector<int>>(1, vector<int>(1, 0));
    auto pre = generate(n-1);
    const int N = (1<<n);
    const int h = N/2;
    vector<vector<int>> res(N, vector<int>(N, 0));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int c = pre[i%h][j%h];
            res[i][j] = (i >= h && j >= h ? 1 - c : c);
        }
    }
    return res;
}

int main(){
    int N, M;
    while(cin >> N >> M){
        auto sum = generate(min(N, M));
        vector<vector<int>> res((1<<N)-1, vector<int>((1<<M)-1, 0));
        const int c = 1 << (min(N, M));
        for(int i=0;i<res.size();i++){
            for(int j=0;j<res[i].size();j++){
                for(int di=0;di<2;di++){
                    for(int dj=0;dj<2;dj++){
                        res[i][j] += sum[(i+di)%c][(j+dj)%c];
                    }
                }
                res[i][j] %= 2;
            }
        }
        for(auto& v : res){
            for(auto& t : v) cout << t;
            cout << endl;
        }
    }
}