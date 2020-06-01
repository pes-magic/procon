// 順列
// verified
// https://atcoder.jp/contests/agc031/tasks/agc031_d

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
