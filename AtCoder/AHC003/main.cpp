#include <algorithm>
#include <array>
#include <chrono>
#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
class Timer {
public:
	explicit Timer()
		: mStart(chrono::system_clock::now())
	{}
	void start() { mStart = chrono::system_clock::now(); }
	double msec() const {
		auto t = chrono::system_clock::now();
		return 1e-3 * chrono::duration_cast<std::chrono::microseconds>(t - mStart).count();
	}
private:
	chrono::system_clock::time_point mStart;
};

//------------------------------------------------------------------------------
class XorShift {
public:
	using result_type = uint32_t;
	explicit XorShift(result_type seed){ init(seed); }
	void init(result_type s){
		x = 1812433253U * (s ^ (s >> 30));
		y = 1812433253U * (x ^ (x >> 30)) + 1;
		z = 1812433253U * (y ^ (y >> 30)) + 2;
		w = 1812433253U * (z ^ (z >> 30)) + 3;
	}
	static constexpr result_type min() { return numeric_limits<result_type>::min(); }
	static constexpr result_type max() { return numeric_limits<result_type>::max(); }
	result_type operator() () {
		result_type t = x ^ (x << 11);
		x = y; y = z; z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
private:
	result_type x;
	result_type y;
	result_type z;
	result_type w;
};

//------------------------------------------------------------------------------
int search_step = 76;
double r_pow = 0.7063953827425218;
double call_mul = 860.0655929452138;
int switch_pos = 120;
int switch_margin = 60;

//------------------------------------------------------------------------------
class LeastSquare {
public:
    explicit LeastSquare()
        : mRng(1000000007)
    {
        mSumX.fill(0);
        mSumY.fill(0);
        mCntX.fill(0);
        mCntY.fill(0);
        for(int i=0;i<60;i++) mAvg[i] = 1.0;
        for(int i=60;i<120;i++) mAvg[i] = 1.1;
        mResult = mAvg;
    }
    string query(int x1, int y1, int x2, int y2) const {
        vector<vector<double>> cost(30, vector<double>(30, 1e12));
        vector<string> prev(30, string(30, '-'));
        cost[x2][y2] = 0.0;
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> qu;
        qu.emplace(0.0, 32*x2+y2);
        const string dir = "URDL";
        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, 1, 0, -1};
        double r = max(0, search_step - (int)mHistory.size()) * (1.0/search_step);
        if(r > 0) r = pow(r, r_pow);
        // double r = 0.0;
        while(!qu.empty()){
            auto p = qu.top(); qu.pop();
            const int x = p.second/32;
            const int y = p.second%32;
            if(cost[x][y] < p.first) continue;
            for(int i=0;i<4;i++){
                const int nx = x + dx[i];
                const int ny = y + dy[i];
                if(nx < 0 || 30 <= nx || ny < 0 || 30 <= ny) continue;
                const int idxX = 2 * x + (y + min(0, dy[i])) / 15;
                const int idxY = 2 * y + (x + min(0, dx[i])) / 15;
                const double nc = p.first + (i%2 == 0 ? mResult[idxY+60] : mResult[idxX]) + r * call_mul * ((i%2 == 0 ? mCntY[idxY] : mCntX[idxX]) + 1);
                if(nc < cost[nx][ny]){
                    prev[nx][ny] = (i+2)%4 + '0';
                    cost[nx][ny] = nc;
                    qu.emplace(nc, 32*nx+ny);
                }
            }
        }
        string s;
        int cx = x1, cy = y1;
        while(cx != x2 || cy != y2){
            int pd = prev[cx][cy] - '0';
            s.push_back(dir[pd]);
            cx += dx[pd];
            cy += dy[pd];
        }
        return s;
    }
    void update(int x1, int y1, int x2, int y2, const string& response, int score){
        array<int, 121> cur;
        cur.fill(0);
        cur.back() = score;
        double unit = (double)score/response.size();
        for(auto& c : response){
            if(c == 'U' || c == 'D'){
                if(c == 'U') x1--;
                const int idx = 2*y1+x1/15;
                cur[idx+60]++;
                mSumY[idx] += unit;
                mCntY[idx]++;
                if(c == 'D') x1++;
            } else {
                if(c == 'L') y1--;
                const int idx = 2*x1+y1/15;
                cur[idx]++;
                mSumX[idx] += unit;
                mCntX[idx]++;
                if(c == 'R') y1++;
            }
        }
        mHistory.emplace_back(cur);
        for(int i=0;i<60;i++){
            if(mCntX[i] > 0) mAvg[i] = mSumX[i]/mCntX[i];
            else if(mCntX[i^1] > 0) mAvg[i] = mSumX[i^1]/mCntX[i^1];
            if(mCntY[i] > 0) mAvg[i+60] = mSumY[i]/mCntY[i];
            else if(mCntY[i^1] > 0) mAvg[i+60] = mSumY[i^1]/mCntY[i^1];
        }
        array<array<double, 121>, 120> a;
        for(auto& v : a) v.fill(0.0);
        for(int i=0;i<120;i++){
            for(auto& h : mHistory){
                if(h[i] == 0) continue;
                for(int j=0;j<=120;j++){
                    a[i][j] += h[i] * h[j];
                }
            }
        }
        const int n = 120;
        if(mHistory.size() < n){
            mResult = mAvg;
        } else {
            for(int i=0;i<n;i++){
                int pivot = i;
                for(int j=i+1;j<n;j++)
                    if(abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
                if(abs(a[pivot][i]) > 1e-9){
                    swap(a[i], a[pivot]);
                } else {
                    a[i][i] = 1.0;
                    a[i].back() += mAvg[i];
                }
                double div = a[i][i];
                for(int j=0;j<=n;j++) a[i][j] /= div;
                for(int j=i+1;j<n;j++){
                    double mul = a[j][i];
                    for(int k=0;k<=n;k++)
                        a[j][k] -= a[i][k]*mul;
                }
            }
            for(int i=n-1;i>=0;i--){
                for(int j=0;j<i;j++){
                    a[j][n] -= a[j][i]*a[i][n];
                }
                mResult[i] = max(0.0, a[i].back());
            }
        }
        // if(mHistory.size()%100 == 0){
        //     double e1 = 0.0, e2 = 0.0;
        //     for(auto& h : mHistory){
        //         double s1 = 0.0, s2 = 0.0;
        //         for(int i=0;i<120;i++){
        //             s1 += h[i] * mResult[i];
        //             s2 += h[i] * mAvg[i];
        //         }
        //         e1 += (s1-h.back()) * (s1-h.back());
        //         e2 += (s2-h.back()) * (s2-h.back());
        //     }
        //     // cout << mHistory.size() << " " << e1 << " " << e2 << endl;
        // }

        // if(mHistory.size()%250 == 0){
        //     for(int i=0;i<30;i++) cout << mResult[i] << " "; cout << endl;
        //     for(int i=30;i<60;i++) cout << mResult[i] << " "; cout << endl;
        // }
    }
    double getEdgeH(int x, int y) const {
        return mResult[2*x+y/15];
    }
    double getEdgeV(int x, int y) const {
        return mResult[2*y+x/15+60];
    }
private:
    array<double, 60> mSumX;
    array<double, 60> mSumY;
    array<int, 60> mCntX;
    array<int, 60> mCntY;
    vector<array<int, 121>> mHistory;
    array<double, 120> mAvg;
    array<double, 120> mResult;
    mutable XorShift mRng;
};

//------------------------------------------------------------------------------
class LeastSquareNew {
public:
    explicit LeastSquareNew()
        : mRng(1000000007)
    {
        mSumV.fill(0);
        mSumH.fill(0);
        for(auto& v : mSumFullV) v.fill(0);
        for(auto& v : mSumFullH) v.fill(0);
        mCntV.fill(0);
        mCntH.fill(0);
        for(auto& v : mCntFullV) v.fill(0);
        for(auto& v : mCntFullH) v.fill(0);
        for(int i=0;i<60;i++) mAvg[i] = 1.0;
        for(int i=60;i<120;i++) mAvg[i] = 1.1;
        mResult = mAvg;
        mThrH.fill(15);
        mThrV.fill(15);
        mHistory.reserve(1000);
        mHistoryFullH.reserve(1000);
        mHistoryFullV.reserve(1000);
    }
    string query(int x1, int y1, int x2, int y2) const {
        vector<vector<double>> cost(30, vector<double>(30, 1e12));
        vector<string> prev(30, string(30, '-'));
        cost[x2][y2] = 0.0;
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> qu;
        qu.emplace(0.0, 32*x2+y2);
        const string dir = "URDL";
        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, 1, 0, -1};
        double r = max(0, search_step - (int)mHistory.size()) * (1.0/search_step);
        if(r > 0) r = pow(r, r_pow);
        // double r = 0.0;
        while(!qu.empty()){
            auto p = qu.top(); qu.pop();
            const int x = p.second/32;
            const int y = p.second%32;
            if(cost[x][y] < p.first) continue;
            for(int i=0;i<4;i++){
                const int nx = x + dx[i];
                const int ny = y + dy[i];
                if(nx < 0 || 30 <= nx || ny < 0 || 30 <= ny) continue;
                const int idxH = 2 * x + ((y + min(0, dy[i])) >= mThrH[x]);
                const int idxV = 2 * y + ((x + min(0, dx[i])) >= mThrV[y]);
                const double nc = p.first + (i%2 == 0 ? mResult[idxV+60] : mResult[idxH]) + r * call_mul * ((i%2 == 0 ? mCntV[idxV] : mCntH[idxH]) + 1);
                if(nc < cost[nx][ny]){
                    prev[nx][ny] = (i+2)%4 + '0';
                    cost[nx][ny] = nc;
                    qu.emplace(nc, 32*nx+ny);
                }
            }
        }
        string s;
        int cx = x1, cy = y1;
        while(cx != x2 || cy != y2){
            int pd = prev[cx][cy] - '0';
            s.push_back(dir[pd]);
            cx += dx[pd];
            cy += dy[pd];
        }
        return s;
    }
    void update(int x1, int y1, int x2, int y2, const string& response, int score){
        array<int, 121> cur;
        array<array<int, 29>, 30> curH;
        array<array<int, 30>, 29> curV;
        for(auto& v : curH) v.fill(0);
        for(auto& v : curV) v.fill(0);
        cur.fill(0);
        cur.back() = score;
        double unit = (double)score/response.size();
        for(auto& c : response){
            if(c == 'U' || c == 'D'){
                if(c == 'U') x1--;
                const int idx = 2 * y1 + (x1 >= mThrV[y1]);
                cur[idx+60]++;
                curV[x1][y1]++;
                mSumV[idx] += unit;
                mSumFullV[x1][y1] += unit;
                mCntV[idx]++;
                mCntFullV[x1][y1] += unit;
                if(c == 'D') x1++;
            } else {
                if(c == 'L') y1--;
                const int idx = 2 * x1 + (y1 >= mThrH[x1]);
                cur[idx]++;
                curH[x1][y1]++;
                mSumH[idx] += unit;
                mSumFullH[x1][y1] += unit;
                mCntH[idx]++;
                mCntFullH[x1][y1]++;
                if(c == 'R') y1++;
            }
        }
        mHistory.emplace_back(cur);
        mHistoryFullH.emplace_back(curH);
        mHistoryFullV.emplace_back(curV);
        for(int i=0;i<60;i++){
            if(mCntH[i] > 0) mAvg[i] = mSumH[i]/mCntH[i];
            else if(mCntH[i^1] > 0) mAvg[i] = mSumH[i^1]/mCntH[i^1];
            if(mCntV[i] > 0) mAvg[i+60] = mSumV[i]/mCntV[i];
            else if(mCntV[i^1] > 0) mAvg[i+60] = mSumV[i^1]/mCntV[i^1];
        }
        updateResult();

        // if(mHistory.size() == 200){
        //     for(int i=0;i<30;i++){
        //         while(true){
        //             double curErr = calcCurrentError();
        //             auto curResult = mResult;
        //             if(mResult[2*i] < mResult[2*i+1]){
        //                 if(mThrH[i] == 1) break;
        //                 minusThrH(i);
        //                 updateResult();
        //                 double err = calcCurrentError();
        //                 if(err < curErr) continue;
        //                 plusThrH(i);
        //                 mResult = curResult;
        //             } else {
        //                 if(mThrH[i] == 28) break;
        //                 plusThrH(i);
        //                 updateResult();
        //                 double err = calcCurrentError();
        //                 if(err < curErr) continue;
        //                 minusThrH(i);
        //                 mResult = curResult;
        //             }
        //             break;
        //         }
        //         while(true){
        //             double curErr = calcCurrentError();
        //             auto curResult = mResult;
        //             if(mResult[2*i+60] < mResult[2*i+61]){
        //                 if(mThrV[i] == 1) break;
        //                 minusThrV(i);
        //                 updateResult();
        //                 double err = calcCurrentError();
        //                 if(err < curErr) continue;
        //                 plusThrV(i);
        //                 mResult = curResult;
        //             } else {
        //                 if(mThrV[i] == 28) break;
        //                 plusThrV(i);
        //                 updateResult();
        //                 double err = calcCurrentError();
        //                 if(err < curErr) continue;
        //                 minusThrV(i);
        //                 mResult = curResult;
        //             }
        //             break;
        //         }
        //     }
        // }

        if(mHistory.size() > 200 && mHistory.size() < 700){
            int i = mRng()%30;
            auto curResult = mResult;
            const double curErr = calcCurrentError();
            if(mRng()%2){
                if(mThrH[i] < 15 || (mThrH[i] == 15 && mRng()%2)){
                    if(mThrH[i] > 1){
                        minusThrH(i);
                        updateResult();
                        double err = calcCurrentError();
                        if(err >= curErr){
                            plusThrH(i);
                            mResult = curResult;
                        }
                    }
                } else {
                    if(mThrH[i] < 28){
                        plusThrH(i);
                        updateResult();
                        double err = calcCurrentError();
                        if(err >= curErr){
                            minusThrH(i);
                            mResult = curResult;
                        }
                    }
                }
            } else {
                if(mThrV[i] < 15 || (mThrV[i] == 15 && mRng()%2)){
                    if(mThrV[i] > 1){
                        minusThrV(i);
                        updateResult();
                        double err = calcCurrentError();
                        if(err >= curErr){
                            plusThrV(i);
                            mResult = curResult;
                        }
                    }
                } else {
                    if(mThrV[i] < 28){
                        plusThrV(i);
                        updateResult();
                        double err = calcCurrentError();
                        if(err >= curErr){
                            minusThrV(i);
                            mResult = curResult;
                        }
                    }
                }
            }
        }
        // if(mHistory.size()%100 == 0){
        //     double e1 = 0.0, e2 = 0.0;
        //     for(auto& h : mHistory){
        //         double s1 = 0.0, s2 = 0.0;
        //         for(int i=0;i<120;i++){
        //             s1 += h[i] * mResult[i];
        //             s2 += h[i] * mAvg[i];
        //         }
        //         e1 += (s1-h.back()) * (s1-h.back());
        //         e2 += (s2-h.back()) * (s2-h.back());
        //     }
        //     // cout << mHistory.size() << " " << e1 << " " << e2 << endl;
        // }
        // if(mHistory.size() == 1000){
        //     for(int i=0;i<30;i++) cout << i << " " << mThrH[i] << " " << mResult[2*i] << " " << mResult[2*i+1] << endl;
        // }

        // if(mHistory.size()%250 == 0){
        //     for(int i=0;i<30;i++) cout << mResult[i] << " "; cout << endl;
        //     for(int i=30;i<60;i++) cout << mResult[i] << " "; cout << endl;
        // }
    }
    double getEdgeH(int x, int y) const {
        return mResult[2 * x + (y >= mThrH[x])];
    }
    double getEdgeV(int x, int y) const {
        return mResult[2 * y + (x >= mThrV[y]) + 60];
    }
private:
    void updateResult(){
        const int n = 120;
        if(mHistory.size() < switch_pos){
            mResult = mAvg;
        } else {
            array<array<double, 121>, 120> a;
            for(auto& v : a) v.fill(0.0);
            for(int i=0;i<120;i++){
                for(auto& h : mHistory){
                    if(h[i] == 0) continue;
                    for(int j=0;j<=120;j++){
                        a[i][j] += h[i] * h[j];
                    }
                }
            }
            for(int i=0;i<n;i++){
                int pivot = i;
                for(int j=i+1;j<n;j++)
                    if(abs(a[j][i]) > abs(a[pivot][i])) pivot = j;
                if(abs(a[pivot][i]) > 1e-9){
                    swap(a[i], a[pivot]);
                } else {
                    a[i][i] = 1.0;
                    a[i].back() += mAvg[i];
                }
                double div = a[i][i];
                for(int j=0;j<=n;j++) a[i][j] /= div;
                for(int j=i+1;j<n;j++){
                    double mul = a[j][i];
                    for(int k=0;k<=n;k++)
                        a[j][k] -= a[i][k]*mul;
                }
            }
            for(int i=n-1;i>=0;i--){
                for(int j=0;j<i;j++){
                    a[j][n] -= a[j][i]*a[i][n];
                }
                mResult[i] = max(0.0, a[i].back());
            }
        }
        if(switch_pos <= mHistory.size() && mHistory.size() < switch_pos + switch_margin){
            double ratio = (mHistory.size() - switch_pos)/(double)switch_margin;
            for(int i=0;i<mResult.size();i++) mResult[i] = ratio * mResult[i] + (1-ratio) * mAvg[i];
        }
    }
    void minusThrH(int x){
        --mThrH[x];
        mSumH[2*x] -= mSumFullH[x][mThrH[x]];
        mSumH[2*x+1] += mSumFullH[x][mThrH[x]];
        mCntH[2*x] -= mCntFullH[x][mThrH[x]];
        mCntH[2*x+1] += mCntFullH[x][mThrH[x]];
        if(mCntH[2*x] > 0) mAvg[2*x] = mSumH[2*x]/mCntH[2*x];
        else if(mCntH[2*x+1] > 0) mAvg[2*x] = mSumH[2*x+1]/mCntH[2*x+1];
        if(mCntH[2*x+1] > 0) mAvg[2*x+1] = mSumH[2*x+1]/mCntH[2*x+1];
        else if(mCntH[2*x] > 0) mAvg[2*x+1] = mSumH[2*x]/mCntH[2*x];
        for(int i=0;i<mHistory.size();i++){
            mHistory[i][2*x] -= mHistoryFullH[i][x][mThrH[x]];
            mHistory[i][2*x+1] += mHistoryFullH[i][x][mThrH[x]];
        }
    }
    void plusThrH(int x){
        mSumH[2*x] += mSumFullH[x][mThrH[x]];
        mSumH[2*x+1] -= mSumFullH[x][mThrH[x]];
        mCntH[2*x] += mCntFullH[x][mThrH[x]];
        mCntH[2*x+1] -= mCntFullH[x][mThrH[x]];
        if(mCntH[2*x] > 0) mAvg[2*x] = mSumH[2*x]/mCntH[2*x];
        else if(mCntH[2*x+1] > 0) mAvg[2*x] = mSumH[2*x+1]/mCntH[2*x+1];
        if(mCntH[2*x+1] > 0) mAvg[2*x+1] = mSumH[2*x+1]/mCntH[2*x+1];
        else if(mCntH[2*x] > 0) mAvg[2*x+1] = mSumH[2*x]/mCntH[2*x];
        for(int i=0;i<mHistory.size();i++){
            mHistory[i][2*x] += mHistoryFullH[i][x][mThrH[x]];
            mHistory[i][2*x+1] -= mHistoryFullH[i][x][mThrH[x]];
        }
        ++mThrH[x];
    }
    void minusThrV(int y){
        --mThrV[y];
        mSumV[2*y] -= mSumFullV[mThrV[y]][y];
        mSumV[2*y+1] += mSumFullV[mThrV[y]][y];
        mCntV[2*y] -= mCntFullV[mThrV[y]][y];
        mCntV[2*y+1] += mCntFullV[mThrV[y]][y];
        if(mCntV[2*y] > 0) mAvg[2*y+60] = mSumV[2*y]/mCntV[2*y];
        else if(mCntV[2*y+1] > 0) mAvg[2*y+60] = mSumV[2*y+1]/mCntV[2*y+1];
        if(mCntV[2*y+1] > 0) mAvg[2*y+61] = mSumV[2*y+1]/mCntV[2*y+1];
        else if(mCntV[2*y] > 0) mAvg[2*y+61] = mSumV[2*y]/mCntV[2*y];
        for(int i=0;i<mHistory.size();i++){
            mHistory[i][2*y+60] -= mHistoryFullV[i][mThrV[y]][y];
            mHistory[i][2*y+61] += mHistoryFullV[i][mThrV[y]][y];
        }
    }
    void plusThrV(int y){
        mSumV[2*y] += mSumFullV[mThrV[y]][y];
        mSumV[2*y+1] -= mSumFullV[mThrV[y]][y];
        mCntV[2*y] += mCntFullV[mThrV[y]][y];
        mCntV[2*y+1] -= mCntFullV[mThrV[y]][y];
        if(mCntV[2*y] > 0) mAvg[2*y+60] = mSumV[2*y]/mCntV[2*y];
        else if(mCntV[2*y+1] > 0) mAvg[2*y+60] = mSumV[2*y+1]/mCntV[2*y+1];
        if(mCntV[2*y+1] > 0) mAvg[2*y+61] = mSumV[2*y+1]/mCntV[2*y+1];
        else if(mCntV[2*y] > 0) mAvg[2*y+61] = mSumV[2*y]/mCntV[2*y];
        for(int i=0;i<mHistory.size();i++){
            mHistory[i][2*y+60] += mHistoryFullV[i][mThrV[y]][y];
            mHistory[i][2*y+61] -= mHistoryFullV[i][mThrV[y]][y];
        }
        ++mThrV[y];
    }
    double calcCurrentError(){
        double e = 0.0;
        for(auto& h : mHistory){
            double s = 0.0;
            for(int i=0;i<120;i++) s += h[i] * mResult[i];
            e += (s-h.back()) * (s-h.back());
        }
        return e;
    }
private:
    array<double, 60> mSumV;
    array<double, 60> mSumH;
    array<array<double, 29>, 30> mSumFullH;
    array<array<double, 30>, 29> mSumFullV;
    array<int, 60> mCntV;
    array<int, 60> mCntH;
    array<array<int, 29>, 30> mCntFullH;
    array<array<int, 30>, 29> mCntFullV;
    vector<array<int, 121>> mHistory;
    vector<array<array<int, 29>, 30>> mHistoryFullH;
    vector<array<array<int, 30>, 29>> mHistoryFullV;
    array<int, 30> mThrH;
    array<int, 30> mThrV;
    array<double, 120> mAvg;
    array<double, 120> mResult;
    mutable XorShift mRng;
};

//------------------------------------------------------------------------------
template<typename T>
void test(T solver){
    for(int _=0;_<1000;_++){
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        auto res = solver.query(x1, y1, x2, y2);
        cout << res << endl;
        int score; cin >> score;
        solver.update(x1, y1, x2, y2, res, score);
    }
}

//------------------------------------------------------------------------------
template<typename T>
void localTest(T solver){
    array<array<int, 29>, 30> lineH;
    array<array<int, 30>, 29> lineV;
    for(auto& v : lineH){
        for(auto& t : v) cin >> t;
    }
    for(auto& v : lineV){
        for(auto& t : v) cin >> t;
    }
    auto errorCheck = [&](){
        double d = 0.0;
        for(int x=0;x<30;x++){
            for(int y=0;y<30;y++){
                if(y < 29){
                    double a = solver.getEdgeH(x, y);
                    double e = lineH[x][y];
                    d += (a-e)*(a-e);
                }
                if(x < 29){
                    double a = solver.getEdgeV(x, y);
                    double e = lineV[x][y];
                    d += (a-e)*(a-e);
                }
            }
        }
        return sqrt(d/(2*30*29));
    };
    double score = 0.0;
    for(int _=0;_<1000;_++){
        int x1, y1, x2, y2, opt; double e;
        cin >> x1 >> y1 >> x2 >> y2 >> opt >> e;
        auto s = solver.query(x1, y1, x2, y2);
        int actual = 0;
        int x = x1, y = y1;
        for(auto& c : s){
            switch(c){
                case 'U': {
                    --x;
                    actual += lineV[x][y];
                } break;
                case 'D': {
                    actual += lineV[x][y];
                    ++x;
                } break;
                case 'L': {
                    --y;
                    actual += lineH[x][y];
                } break;
                case 'R': {
                    actual += lineH[x][y];
                    ++y;
                }
            }
        }
        if(_%50 == 49){
            std::cout << _ << ": " << errorCheck() << endl;
        }
        score = 0.998 * score + (double)opt/actual;
        solver.update(x1, y1, x2, y2, s, (int)(e*actual));
    }
    std::cerr << "Score = " << (int)(2312311 * score) << std::endl;
}

int main(int argc, char *argv[]){
    if(argc >= 2) search_step = atof(argv[1]);
    if(argc >= 3) r_pow = atof(argv[2]);
    if(argc >= 4) call_mul = atof(argv[3]);
    if(argc >= 5) switch_pos = atof(argv[4]);
    if(argc >= 6) switch_margin = atof(argv[5]);

    // NaiveAverage2 solver;
    LeastSquareNew solver;
    test(solver);
    // localTest(solver);
}