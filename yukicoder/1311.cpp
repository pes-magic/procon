#include <iostream>
#include <vector>

using namespace std;

long long getOrder(const vector<int>& v){
    const int N = v.size();
    vector<int> used(N+1, 0);
    long long res = 0;
    for(int i=0;i<N-1;i++){
        res *= N-i;
        int add = v[i]-1;
        for(int j=1;j<v[i];j++) add -= used[j];
        used[v[i]] = 1;
        res += add;
    }
    return res;
}

vector<int> getPerm(long long s, int N){
    vector<long long> fact(N);
    fact[0] = fact[1] = 1;
    for(int i=2;i<N;i++) fact[i] = i * fact[i-1];
    vector<int> used(N, 0);
    vector<int> res;
    for(int i=0;i<N;i++){
        int ord = s/fact[N-1-i];
        s %= fact[N-1-i];
        for(int j=0;j<N;j++){
            if(used[j]) continue;
            if(ord == 0){
                res.push_back(j+1);
                used[j] = 1;
                break;
            }
            --ord;
        }
    }
    return res;
}


int main(){
    int N;
    long long S;
    cin >> S >> N;
    auto v = getPerm(S, N);
    vector<int> r(N);
    for(int i=0;i<N;i++) r[v[i]-1] = i+1;
    cout << getOrder(r) << endl;
}