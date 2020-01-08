#include <iostream>
#include <vector>

using namespace std;

class Sum {
public:
    explicit Sum(const vector<long long>& v) : sum(v.size()+1, 0), stepSum(v.size()+1, 0) {
        for(int i=0;i<v.size();i++) sum[i+1] = v[i];
        for(int i=0;i<v.size();i++) stepSum[i+1] = sum[i+1] + sum[i] + stepSum[i];
    }
    long long getStepSum(int s, int e) const {
        return stepSum[e] - stepSum[s] - sum[s];
    }
    long long getSum(int e) const {
        return sum[e];
    }
private:
    vector<long long> sum;
    vector<long long> stepSum;
};

int main(){
    int L, N;
    while(cin >> L >> N){
        vector<long long> X(N), Y(N);
        for(int i=0;i<N;i++){
            cin >> X[i];
            Y[N-i-1] = L - X[i];
        }
        long long res = max(X.back(), Y.back());
        Sum sx(X), sy(Y);
        for(int i=1;i<N;i++){
            int nx = i;
            int ny = N-i;
            int m = min(nx, ny);
            res = max(res, sx.getStepSum(nx-m, nx) + sy.getStepSum(ny-m, ny) + max(sx.getSum(nx), sy.getSum(ny)));
            {
                int mx = min(m+1, nx);
                int my = mx - 1;
                if(my > 0){
                    res = max(res, sx.getStepSum(nx-mx, nx) + sy.getStepSum(ny-my, ny) + sy.getSum(ny));
                }
            }
            {
                int my = min(m+1, ny);
                int mx = my - 1;
                if(mx > 0){
                    res = max(res, sx.getStepSum(nx-mx, nx) + sy.getStepSum(ny-my, ny) + sx.getSum(nx));
                }
            }
        }
        cout << res << endl;
    }
}