#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Frac {
public:
    explicit Frac(long long a = 0, long long b = 1) : a(a), b(b) {}
    bool operator < (const Frac& f) const { return a * f.b < f.a * b; }
    long long a, b;
};

vector<vector<long long>> makeSum(const vector<long long>& v){
    vector<vector<long long>> res;
    res.push_back(vector<long long>(1, v[0]));
    for(int i=1;i<v.size();i++){
        res.push_back(res.back());
        long long sum = 0;
        for(int j=0;j<res.back().size();j++){
            sum += v[i-j];
            res.back()[j] = max(res.back()[j], sum);
        }
        sum += v[0];
        res.back().push_back(sum);
    }
    return res;
}

long long solve(const vector<long long>& W, const vector<long long>& H){
    vector<pair<Frac, int>> lines;
    lines.emplace_back(Frac(-(1LL<<40), 1), 0);
    for(int i=1;i<W.size();i++){
        while(!lines.empty()){
            auto last = lines.back().second;
            Frac f(-(W[i] - W[last]), i-last);
            if(lines.back().first < f){
                lines.emplace_back(f, i);
                break;
            } else {
                lines.pop_back();
            }
        }
    }
    long long res = -(1LL << 60);
    for(int i=0;i<H.size();i++){
        auto it = lower_bound(lines.begin(), lines.end(), make_pair(Frac(H[i], i+1), (int)W.size()));
        --it;
        int idx = it->second;
        res = max(res, (idx+1)*H[i]+(i+1)*W[idx]);
    }
    return res;
}

int main(){
    int W, H;
    while(cin >> W >> H){
        vector<long long> a(W), b(H);
        for(auto& t : a) cin >> t;
        for(auto& t : b) cin >> t;
        auto sumsW = makeSum(a);
        auto sumsH = makeSum(b);
        int Q; cin >> Q;
        for(int i=0;i<Q;i++){
            int A, B; cin >> A >> B;
            cout << solve(sumsW[A-1], sumsH[B-1]) << endl;
        }
    }
}