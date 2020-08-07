#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N; cin >> N;
    vector<string> A(N);
    vector<string> B(N);
    vector<string> C(N, string(N, '1'));
    for(auto& s : A) cin >> s;
    for(auto& s : B) cin >> s;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(B[i][j] == '1') continue;
            for(int k=0;k<N;k++){
                if(A[i][k] == '1') C[k][j] = '0';
            }
        }
    }
    bool valid = true;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(B[i][j] == '0') continue;
            bool ok = false;
            for(int k=0;k<N;k++){
                if(A[i][k] == '1' && C[k][j] == '1') ok = true;
            }
            if(!ok) valid = false;
        }
    }
    if(valid){
        for(auto& s : C) cout << s << endl;
    } else {
        cout << -1 << endl;
    }
}