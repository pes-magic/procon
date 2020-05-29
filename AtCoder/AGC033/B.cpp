#include <iostream>
#include <string>

using namespace std;

bool fall(const string& S, const string& T, char left, char right, int start, int width){
    int l = 0, r = width + 1;
    for(int i=S.size()-1;i>=0;i--){
        if(r <= l+1) return true;
        if(T[i] == right) l = max(0, l-1);
        if(T[i] == left) r = min(width+1, r+1);
        if(S[i] == left) ++l;
        if(S[i] == right) --r;
    }
    return (start <= l || r <= start);
}

int main(){
    int H, W, N; cin >> H >> W >> N;
    int sr, sc; cin >> sr >> sc;
    string S, T; cin >> S >> T;
    cout << (fall(S, T, 'L', 'R', sc, W) || fall(S, T, 'U', 'D', sr, H) ? "NO": "YES") << endl;
}