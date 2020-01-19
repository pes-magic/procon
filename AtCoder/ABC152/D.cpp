#include <iostream>
#include <vector>

using namespace std;

int back(int t){
    while(t >= 10) t /= 10;
    return t;
}

int main(){
    int N;
    while(cin >> N){
        vector<vector<long long>> cnt(10, vector<long long>(10, 0));
        for(int i=1;i<=N;i++){
            ++cnt[back(i)][i%10];
        }
        long long res = 0;
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                res += cnt[i][j] * cnt[j][i];
            }
        }
        cout << res << endl;
    }
}