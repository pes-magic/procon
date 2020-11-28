#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N; cin >> N;
    string S; cin >> S;
    vector<char> vc;
    for(auto& c : S){
        vc.push_back(c);
        int n = vc.size();
        if(n >= 3 && vc[n-3] == 'f' && vc[n-2] == 'o' && vc[n-1] == 'x'){
            for(int i=0;i<3;i++) vc.pop_back();
        }
    }
    cout << vc.size() << endl;
}