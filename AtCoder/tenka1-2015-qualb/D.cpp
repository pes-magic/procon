#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

char toDigit(char c){
    switch(c){
        case 'O':
        case 'D':
            return '0';
        case 'I':
            return '1';
        case 'Z':
            return '2';
        case 'E':
            return '3';
        case 'h':
            return '4';
        case 's':
            return '5';
        case 'q':
            return '6';
        case 'L':
            return '7';
        case 'B':
            return '8';
        case 'G':
            return '9';
    }
    return '~';
}

string toNumber(const string& s){
    string res = "";
    for(int i=s.size()-1;i>=0;i--) res += toDigit(s[i]);
    return res;
}

int main(){
    int D, N; cin >> D >> N;
    vector<string> res(D+1, "");
    vector<string> word;
    for(int i=0;i<N;i++){
        string s; cin >> s;
        word.emplace_back(toNumber(s));
    }
    sort(word.begin(), word.end(), [](const string& s, const string& t){ return s+t > t+s; });
    for(auto& s : word){
        for(int i=D-s.size();i>=0;i--){
            if(res[i].size() != i) continue;
            res[i+s.size()] = max(res[i+s.size()], res[i]+s);
        }
    }
    string best = "";
    for(int i=D;i>0;i--){
        if(res[i].empty()) continue;
        if(res[i][0] != '0'){
            best = res[i];
            break;
        } else {
            best = max(best, res[i]);
        }
    }
    if(best[0] == '0'){
        while(!best.empty() && best.back() == '0') best.pop_back();
        if(best.empty()){
            cout << "0" << endl;
        } else {
            cout << "0." << best.substr(1) << endl;
        }
    } else {
        cout << best << endl;
    }
}