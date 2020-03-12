#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int t){
    for(int i=2;i*i<=t;i++){
        if(t%i==0) return false;
    }
    return true;
}

int main(){
    auto getN = [](int K){ return K*(K-1) + 1; };
    int K = 1, N = getN(1);
    while(!isPrime(K-1) || N < 1000){
        ++K;
        N = getN(K);
    }
    cout << N << " " << K << endl;
    vector<vector<int>> A(N, vector<int>(N, 0));
    for(int i=0;i<K;i++){
        A[i][0] = 1;
        for(int j=0;j<K-1;j++){
            A[i][1+i*(K-1)+j] = 1;
        }
    }
    for(int i=K;i<N;i++){
        A[i][(i-1)/(K-1)] = 1;
    }
    for(int i=0;i<K-1;i++){
        for(int j=0;j<K-1;j++){
            int s = (i*j)%(K-1);
            for(int k=0;k<K-1;k++){
                A[K+i*(K-1)+k][K+j*(K-1)+(k+s)%(K-1)] = 1;
            }
        }
    }
    for(auto& v : A){
        bool first = true;
        for(int i=0;i<N;i++){
            if(!v[i]) continue;
            if(first) first = false;
            else cout << " ";
            cout << i+1;
        }
        cout << endl;
    }
}