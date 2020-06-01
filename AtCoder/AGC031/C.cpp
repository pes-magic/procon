#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<int> gen(int N, int dif){
    if(N == 1) return {0, 1};
    auto prev = gen(N%2 == 0 ? N-1 : N-2, dif);
    vector<int> res;
    if(N%2 == 0){
        for(int i=0;i<prev.size();i++){
            res.push_back(2*prev[i]+i%2);
            res.push_back(2*prev[i]+1-i%2);
        }
    } else {
        int v[2][8] = {
            {0, 1, 3, 2, 2, 3, 1, 0},
            {0, 1, 3, 2, 2, 0, 1, 3}
        };
        for(int i=0;i<prev.size();i+=2){
            int type = (N <= dif && i == prev.size() - 2 ? 1 : 0);
            for(int j=0;j<8;j++){
                res.push_back(4*prev[i+j/4] + v[type][j]);
            }
        }
    }
    return res;
}

int main(){
    int N, A, B; cin >> N >> A >> B;
    deque<int> qu;
    int cnt = 0;
    for(int i=0;i<N;i++){
        if(((A^B)>>i)%2){
            qu.push_back(i);
            ++cnt;
        } else {
            qu.push_front(i);
        }
    }
    if(cnt%2 == 0){
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        auto v = gen(N, cnt);
        for(auto& t : v){
            int val = 0;
            for(int i=0;i<qu.size();i++){
                val |= (((A>>qu[i])%2)^((t>>i)%2)) << qu[i];
            }
            cout << val << " ";
        }
        cout << endl;
    }
}