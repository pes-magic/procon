#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    vector<vector<int>> v(N, vector<int>(N));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) v[i][j] = (2*i+2*j)%N;
    }
    vector<int> map(N, 0);
    for(int i=0;i<N;i++) map[v[i][i]] = i+1;
    for(int i=0;i<N;i++){
        cout << map[v[i][0]];
        for(int j=1;j<N;j++) cout << " " << map[v[i][j]];
        cout << endl;
    }
}