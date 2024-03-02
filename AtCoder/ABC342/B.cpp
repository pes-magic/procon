#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    int Q; cin >> Q;
    for(int i = 0; i < Q; i++){
        int B, E; cin >> B >> E;
        for(int t : A){
            if (t==B) {
                cout << B << endl;
                break;
            }
            if (t==E) {
                cout << E << endl;
                break;
            }
        }
    }
}