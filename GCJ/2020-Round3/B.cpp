#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

int solveSmall(int K, const vector<int>& X, const vector<int> T){
    int res = 2*K;
    vector<int> seg(2*K, 0), id(2*K, 0);
    for(auto& t : X) seg[2*t] = 1;
    for(int i=0;i<X.size();i++){
        for(int j=2*X[i];j<(i+1==X.size()?2*K:2*X[i+1]);j++) id[j] = i;
    }
    for(int i=0;i<1<<(2*K);i++){
        bool ok = true;
        for(int j=0;j<2*K;j++) if((i&(1<<j)) && seg[j]) ok = false;
        if(!ok) continue;
        for(int j=0;j<X.size();j++){
            int v = (1 << ((j+1==X.size()?2*K:2*X[j+1]) - 2*X[j])) - 1;
            v <<= 2*X[j];
            if(!(v&i)) ok = false;
        }
        if(!ok) continue;
        vector<int> pos;
        for(int j=0;j<2*K;j++) if(i&(1<<j)) pos.push_back(j);
        for(int j=0;j<pos.size() && ok;j++){
            int cur = pos[j];
            int next = pos[(j+1)%pos.size()];
            if(id[cur] == id[next]) continue;
            if(cur%2 != next%2){ ok = false; continue; }
            int dst = (cur < next ? next : next + 2*K);
            for(int k=cur+1;k<dst;k++){
                int c = k-cur < dst-k ? id[cur] : id[next];
                if(c != id[k%(2*K)]) ok = false;
            }
        }
        if(ok) res = min<int>(res, pos.size());
    }
    return res;
}

bool gaussianElimination(vector<vector<long long>> &a){
	int n = a.size();
	for(int i=0;i<n;i++){
		int pivot = i;
		for(int j=i+1;j<n;j++)
			if(abs(a[j][i])>abs(a[pivot][i])) pivot = j;
		swap(a[i], a[pivot]);
		auto div = a[i][i];
        if(div == 0) return false;
		for(int j=0;j<=n;j++) a[i][j] /= div; // b[i] /= div;
		for(int j=i+1;j<n;j++){
			auto mul = a[j][i];
			for(int k=0;k<=n;k++)
				a[j][k] -= a[i][k]*mul;
		}
	}
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<i;j++){
			a[j][n] -= a[j][i]*a[i][n];
		}
	}
    return true;
}

int solveLarge(long long K, const vector<int>& _X){
    K *= 2;
    vector<long long> X(_X.size());
    for(int i=0;i<X.size();i++) X[i] = _X[i];
    for(auto& t : X) t *= 2;
    const int N = X.size();
    X.push_back(K);
    if(N%2 == 1){
        vector<vector<long long>> a(N, vector<long long>(N+1, 0));
        for(int i=0;i<N;i++){
            a[i][i] = a[i][(i+1)%N] = 1;
            a[i][N] = (i+1 == N ? K : 2 * X[i+1]);
        }
        if(gaussianElimination(a)){
            bool ok = true;
            for(int i=0;i<N;i++){
                int src = X[i];
                int dst = X[i+1];
                if(src < a[i][N] && a[i][N] < dst) continue;
                ok = false;
            }
            if(ok) return N;
        }
    }
    vector<pair<int, int>> pr;
    for(int i=0;i<N;i++){
        int p = X[i+1] - 1;
        int dstIdx = i;
        while(true){
            int np = 2 * X[dstIdx+1] - p;
            if(dstIdx+1 == N) np %= K;
            if(X[dstIdx+2 == N ? N : (dstIdx+2)%N] < np) break;
            dstIdx = (dstIdx+1)%N;
            p = np;
            if(dstIdx == i){
                if(p == X[i+1]-1) return N;
                break;
            }
        }
        if(dstIdx == i){
            pr.emplace_back(i, i);
            continue;
        }
        p = X[i+1] - 1;
        int srcIdx = i;
        while(true){
            int np = 2 * X[srcIdx] - p;
            if(srcIdx == 0) np = (np + K) % K;
            if(np < X[(srcIdx+N-1)%N]) break;
            srcIdx = (srcIdx+N-1)%N;
            p = np;
            if(dstIdx == srcIdx) break;
        }
        pr.emplace_back(srcIdx, dstIdx);
    }
    vector<int> prog(N, 0);
    for(auto& p : pr){
        int d = (p.second <= p.first ? p.second + N: p.second) - p.first;
        int s = p.first;
        while(d){
            prog[s] = max(prog[s], d);
            s = (s+1)%N;
            d--;
        }
    }
    int res = 2*N;
    for(int i=0;i<N;i++){
        int cnt = 0;
        int pos = i;
        int sum = 0;
        while(sum < N){
            int pr = prog[pos];
            pos = (pos + pr) % N;
            sum += pr;
            ++cnt;
        }
        res = min(res, N+cnt);
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int tc=1;tc<=T;tc++){
        int K, N; cin >> K >> N;
        vector<int> X(N), T(N);
        for(auto& t : X) cin >> t;
        for(auto& t : T) cin >> t;
        int ofs = X[0];
        for(auto& t : X) t -= ofs;
        printf("Case #%d: %d\n", tc, solveLarge(K, X));
    }
}