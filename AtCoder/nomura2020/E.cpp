#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string T; cin >> T;
    vector<int> s;
    vector<int> pos;
    int ones = 0;
    for(int i=0;i<T.size();i++){
        if(T[i] == '0'){
            if(ones > 0 && ones%2 == 1){
                s.push_back(i);
            } else {
                pos.push_back(i);
            }
            ones = 0;
        } else {
            s.push_back(i);
            ++ones;
        }
    }
    int turn = s.size();
    long long res = 0;
    while(!pos.empty()){
        int b = pos.back(); pos.pop_back();
        int idx = s.size() - 1;
        while(idx >= 0 && b < s[idx]){
            int p = s[idx];
            int v = T[p] - '0';
            if(idx%2 == 0) res += v * (turn - idx);
            res += (T.size() - turn + idx%2) / 2 * v;
            s.pop_back();
            --idx;
        }
        ++turn;
    }
    for(int i=0;i<s.size();i+=2){
        res += (T.size()-i) * (T[i]-'0');
    }
    cout << res << endl;
}