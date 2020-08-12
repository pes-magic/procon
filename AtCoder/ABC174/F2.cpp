#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Wavelet {
public:
    explicit Wavelet(const vector<unsigned int>& a) : N(a.size()), vb(getDigits_(a), BitVector(a.size())){
        vector<unsigned int> v = a;
        vector<unsigned int> v0(N), v1(N);
        for(int i=vb.size()-1;i>=0;i--){
            maxVal = 2 * maxVal + 1;
            int idx0 = 0, idx1 = 0;
            for(int j=0;j<N;j++){
                if(v[j]&(1<<i)){
                    v1[idx1++] = v[j];
                    vb[i].set(j);
                } else {
                    v0[idx0++] = v[j];
                }
            }
            for(int j=0;j<idx0;j++) v[j]      = v0[j];
            for(int j=0;j<idx1;j++) v[j+idx0] = v1[j];
            vb[i].build();
        }
    }
    int getLeqNum(int val, int end){
        if(end <= 0) return 0;
        if(val < 0) return 0;
        val = min(val, maxVal);
        int res = 0;
        int offset = 0, num = end-1;
        for(int i=vb.size()-1;i>=0;i--){
            if(num < offset) break;
            int rank1 = vb[i].rank(num) - vb[i].rank(offset-1);
            int rank0 = num-offset+1-rank1;
            if(val&(1<<i)){
                if(i == 0) return res + num-offset+1;
                res += rank0;
                offset = N - vb[i].rank(N) + vb[i].rank(offset-1);
                num = offset + rank1 - 1;
            } else {
                if(i == 0) return res + rank0;
                offset = offset - vb[i].rank(offset-1);
                num = offset + rank0 - 1;
            }
        }
        return res;
    }
private:
    int getDigits_(const vector<unsigned int>& a){
        int m = *max_element(a.begin(), a.end());
        int res = 0;
        while(m){ ++res; m /= 2; }
        return max(1, res);
    }
    class BitVector{
    public:
        explicit BitVector(int n=0) : bit((n+63)/64) {}
        void set(int p){
            while(p/64 >= bit.size()) bit.emplace_back(0ULL, 0);
            bit[p/64].first |= 1ULL << (p%64);
        }
        bool get(int p) const {
            if(p/64 >= bit.size()) return false;
            return bit[p/64].first & (1ULL << p%64);
        }
        void build(){
            for(int i=1;i<bit.size();i++)
                bit[i].second = bit[i-1].second + bitCount_(bit[i-1].first);
        }
        int rank(int p) const {
            if(p < 0 || bit.size() == 0) return 0;
            if(p/64 >= bit.size()) return bit.back().second + bitCount_(bit.back().first);
            if(p%64 == 63) return bit[p/64].second + bitCount_(bit[p/64].first);
            return bit[p/64].second + bitCount_(bit[p/64].first & (1ULL << p%64+1)-1);
        }
    private:
        vector<pair<unsigned long long, int>> bit;
        int bitCount_(unsigned long long t) const {
            t = (t&0x5555555555555555ULL)+((t>>1)&0x5555555555555555ULL);
            t = (t&0x3333333333333333ULL)+((t>>2)&0x3333333333333333ULL);
            t = (t&0x0f0f0f0f0f0f0f0fULL)+((t>>4)&0x0f0f0f0f0f0f0f0fULL);
            t = (t&0x00ff00ff00ff00ffULL)+((t>>8)&0x00ff00ff00ff00ffULL);
            t = (t&0x0000ffff0000ffffULL)+((t>>16)&0x0000ffff0000ffffULL);
            t = (t&0x00000000ffffffffULL)+((t>>32)&0x00000000ffffffffULL);
            return t;
        }
    };
private:
    const int N;
    int maxVal = 0;
    vector<BitVector> vb;
};

int main(){
    int N, Q; cin >> N >> Q;
    vector<int> last(N, -1);
    vector<unsigned int> a(N, 0);
    for(int i=0;i<N;i++){
        int t; cin >> t;
        --t;
        if(last[t] != -1) a[i] = last[t] + 1;
        last[t] = i;
    }
    Wavelet wav(a);
    for(int i=0;i<Q;i++){
        int l, r; cin >> l >> r;
        --l;
        cout << r - l - (wav.getLeqNum(r, r) - wav.getLeqNum(l, r)) << endl;
    }
}
