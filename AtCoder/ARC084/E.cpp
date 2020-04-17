#include <iostream>
#include <vector>

using namespace std;

const long long INF = (1LL << 36);

vector<int> solve(int K, int N){
    vector<int> res;
    if(K % 2 == 0){
        res.push_back(K/2);
        for(int i=0;i<N-1;i++) res.push_back(K);
        return res;
    }
    vector<long long> block(N);
    block.back() = 1;
    for(int i=N-2;i>=0;i--){
        block[i] = K * block[i+1] + 1;
        if(block[i] >= INF) block[i] = INF + (block[i] % 2);
    }
    int offset = 0;
    res.push_back((K+1)/2);
    for(int i=1;i<N;i++){
        if(block[i]/2 <= offset){
            long long order = (K * block[i])/2 - offset;
            while(order){
                --order;
                res.push_back(1 + order/block[i]);
                order %= block[i];
                ++i;
            }
            break;
        } else {
            res.push_back((K+1)/2);
            if(block[i]%2 == 1) ++offset;
        }
    }
    return res;
}

int main(){
    int K, N;
    while(cin >> K >> N){
        auto res = solve(K, N);
        cout << res[0];
        for(int i=1;i<res.size();i++) cout << " " << res[i];
        cout << endl;
    }
}