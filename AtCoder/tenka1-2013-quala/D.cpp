#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Parser {
public:
    explicit Parser(const string& _S)
        : S(_S), seek(0), next(_S.size(), -1), len(_S.size(), -1), cycle(_S.size(), -1) 
    { M = parseString(); }
    long long getWholeLen() const { return M; }
    string getStr(long long begin, long long end){
        seek = 0;
        seekLen = 0;
        string res = "";
        getStrImpl_(res, begin, end);
        return res;
    }
private:
    long long parseString(){
        long long res = 0;
        while(seek < S.size() && S[seek] != ')'){
            int start = seek;
            if(isalpha(S[seek])){
                ++res;
                next[start] = seek + 1;
                len[start] = 1;
                cycle[start] = 1;
                ++seek;
            } else if(S[seek] == '('){
                ++seek;
                len[start] = parseString();
                ++seek;
                cycle[start] = parseDigit();
                next[start] = seek;
                res += len[start] * cycle[start];
            }
        }
        return res;
    }
    long long parseDigit(){
        long long res = 0;
        while(seek < S.size() && isdigit(S[seek])){
            res = 10 * res + S[seek] - '0';
            ++seek;
        }
        return res;
    }
    void getStrImpl_(string& res, long long begin, long long end){
        while(seek < S.size() && S[seek] != ')' && seekLen < end){
            int start = seek;
            if(begin < seekLen + len[start] * cycle[start]){
                if(isalpha(S[seek])){
                    if(begin <= seekLen){
                        res += S[seek];
                    }
                    ++seekLen;
                } else {
                    auto offset = max(0LL, (begin - seekLen)/len[start]);
                    seekLen += len[start] * offset;
                    for(auto i=offset;i<cycle[start];i++){
                        seek = start + 1;
                        getStrImpl_(res, begin, end);
                        if(seekLen >= end) break;
                    }
                }
            } else {
                seekLen += len[start] * cycle[start];
            }
            seek = next[start];
        }
    }
private:
    const string S;
    long long M;
    int seek;
    long long seekLen;
    vector<int> next;
    vector<long long> len;
    vector<long long> cycle;
};

int main(){
    long long B, L, N;
    while(cin >> B >> L >> N){
        string S; cin >> S;
        Parser p(S);
        if(B < 0){
            cout << p.getStr(B + p.getWholeLen(), B + L + p.getWholeLen()) << endl;
        } else {
            cout << p.getStr(B, B + L) << endl;
        }
    }
}