#include <iostream>
#include <vector>

using namespace std;

vector<int> inv(const vector<int>& p){
    vector<int> res(p.size());
    for(int i=0;i<p.size();i++) res[p[i]] = i;
    return res;
}

vector<int> mul(const vector<int>& p, const vector<int>& q){
    vector<int> res(p.size());
    for(int i=0;i<p.size();i++) res[i] = p[q[i]];
    return res;
}

vector<int> pow(const vector<int>& p, int K){
    const int N = p.size();
    if(K == 0){
        vector<int> res(N);
        for(int i=0;i<N;i++) res[i] = i;
        return res;
    }
    auto res = pow(p, K/2);
    res = mul(res, res);
    if(K%2 == 1) res = mul(res, p);
    return res;
}

int main(){
    int N, K; cin >> N >> K;
    vector<int> p(N), q(N);
    for(auto& t : p){ cin >> t; --t; }
    for(auto& t : q){ cin >> t; --t; }
    auto pInv = inv(p);
    auto qInv = inv(q);
    auto r = mul(mul(mul(q, pInv), qInv), p);
    r = pow(r, (K-1)/6);
    auto rInv = inv(r);
    auto cur = mul(mul(r, p), rInv);
    auto next = mul(mul(r, q), rInv);
    int k = (K-1)/6*6+1;
    while(k < K){
        auto tmp = next;
        next = mul(next, inv(cur));
        cur = tmp;
        ++k;
    }
    for(auto& t : cur) cout << t+1 << " ";
    cout << endl;
}