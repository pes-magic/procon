#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

void solveSmall(const vector<string>& answer, const vector<int>& score){
    string s = "";
    int ms = 0;
    for(int i=0;i<score.size();i++){
        if(score[i] >= answer[i].size() - score[i]){
            if(ms < score[i]){
                ms = score[i];
                s = answer[i];
            }
        } else {
            if(ms < answer[i].size() - score[i]){
                ms = answer[i].size() - score[i];
                s = answer[i];
                for(auto& c : s) c = (c == 'T' ? 'F' : 'T');
            }
        }
    }
    cout << s << " " << ms << "/1" << endl;
}

string toStr(__int128 v){
    string res = "";
    while(v){
        res += v%10 + '0';
        v /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

__int128 gcd(__int128 a, __int128 b){
    return a%b == 0 ? b : gcd(b, a%b);
}

void solve(const vector<string>& _answer, const vector<int>& _score){
    const int Q = _answer[0].size();
    auto answer = _answer;
    auto score = _score;
    while(answer.size() < 3){
        answer.push_back(_answer[0]);
        score.push_back(_score[0]);
    }
    vector<int> abc, ab, bc, ca;
    for(int i=0;i<Q;i++){
        if(answer[0][i] == answer[1][i] && answer[1][i] == answer[2][i]){
            abc.push_back(i);
        } else if(answer[0][i] == answer[1][i]){
            ab.push_back(i);
        } else if(answer[1][i] == answer[2][i]){
            bc.push_back(i);
        } else {
            ca.push_back(i);
        }
    }
    vector<vector<__int128>> comb(121, vector<__int128>(121, 0));
    for(int i=0;i<=120;i++){
        comb[i][0] = comb[i][i] = 1;
        for(int j=1;j<i;j++){
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
        }
    }
    __int128 all = 0;
    __int128 ex_abc = 0;
    __int128 ex_ab = 0;
    __int128 ex_bc = 0;
    __int128 ex_ca = 0;
    for(int i=0;i<=abc.size();i++){
        if(i > score[0]) break;
        for(int j=0;j<=ab.size();j++){
            if(i+j > score[0]) break;
            for(int k=0;k<=ca.size();k++){
                if(i+j+k > score[0]) break;
                int l = score[0]-i-j-k;
                if(l > bc.size()) continue;
                if(i+j+ca.size()-k+bc.size()-l != score[1]) continue;
                if(i+ab.size()-j+k+bc.size()-l != score[2]) continue;
                all += comb[abc.size()][i] * comb[ab.size()][j] * comb[bc.size()][l] * comb[ca.size()][k];
                if(i > 0 && !abc.empty()){
                    ex_abc += comb[abc.size()-1][i-1] * comb[ab.size()][j] * comb[bc.size()][l] * comb[ca.size()][k];
                }
                if(j > 0 && !ab.empty()){
                    ex_ab += comb[abc.size()][i] * comb[ab.size()-1][j-1] * comb[bc.size()][l] * comb[ca.size()][k];
                }
                if(k > 0 && !ca.empty()){
                    ex_ca += comb[abc.size()][i] * comb[ab.size()][j] * comb[bc.size()][l] * comb[ca.size()-1][k-1];
                }
                if(l > 0 && !bc.empty()){
                    ex_bc += comb[abc.size()][i] * comb[ab.size()][j] * comb[bc.size()-1][l-1] * comb[ca.size()][k];
                }
            }
        }
    }
    __int128 result = 0;
    string f = answer[0];
    for(auto& idx: abc){
        if(2*ex_abc >= all){
            result += ex_abc;
        } else {
            f[idx] = (f[idx] == 'T' ? 'F' : 'T');
            result += all - ex_abc;
        }
    }
    for(auto& idx: ab){
        if(2*ex_ab >= all){
            result += ex_ab;
        } else {
            f[idx] = (f[idx] == 'T' ? 'F' : 'T');
            result += all - ex_ab;
        }
    }
    for(auto& idx: bc){
        if(2*ex_bc >= all){
            result += ex_bc;
        } else {
            f[idx] = (f[idx] == 'T' ? 'F' : 'T');
            result += all - ex_bc;
        }
    }
    for(auto& idx: ca){
        if(2*ex_ca >= all){
            result += ex_ca;
        } else {
            f[idx] = (f[idx] == 'T' ? 'F' : 'T');
            result += all - ex_ca;
        }
    }
    auto g = gcd(result, all);
    result /= g;
    all /= g;
    cout << f << " " << toStr(result) << "/" << toStr(all) << endl;
}

int main(){
    int T; cin >> T;
    for(int i=1;i<=T;i++){
        int N, Q; cin >> N >> Q;
        vector<string> answer(N);
        vector<int> score(N);
        for(int i=0;i<N;i++) cin >> answer[i] >> score[i];
        printf("Case #%d: ", i);
        solve(answer, score);
    }
}
