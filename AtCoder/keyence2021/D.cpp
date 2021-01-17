#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> up(const vector<string>& vs){
    int n = vs.size();
    vector<string> res;
    for(int i=0;i<n;i++) res.emplace_back(vs[i] + "A" + vs[i]);
    res.emplace_back(string(n, 'B') + "B" + string(n, 'A'));
    for(int i=0;i<n;i++) res.emplace_back(vs[i] + "B" + vs[i]);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) res[n+i+1][j] = ('A' + 'B' - res[n+i+1][j]);
    }
    return res;
}

int main(){
    int N; cin >> N;
    vector<string> res(1, "B");
    for(int i=1;i<N;i++) res = up(res);
    cout << res.size() << endl;
    for(auto& s : res) cout << "A" << s << endl;
}