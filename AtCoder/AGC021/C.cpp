#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> try4(int N, int M, int A, int B){
    if(N%2 == 0 || M%2 == 0 || N < 3 || M < 3 || A < 2 || B < 2) return vector<string>();
    vector<string> res(N, string(M, '.'));
    res[N-3][M-3] = res[N-1][M-2] = '<';
    res[N-3][M-2] = res[N-1][M-1] = '>';
    res[N-3][M-1] = res[N-2][M-3] = '^';
    res[N-2][M-1] = res[N-1][M-3] = 'v';
    A -= 2;
    B -= 2;
    for(int i=0;i+1<M-3 && A;i+=2){
        res[N-1][i] = '<';
        res[N-1][i+1] = '>';
        --A;
    }
    for(int j=0;j+1<N-3 && B;j+=2){
        res[j][M-1] = '^';
        res[j+1][M-1] = 'v';
        --B;
    }
    --N; --M;
    for(int i=0;i<N;i+=2){
        for(int j=0;j<M;j+=2){
            if(i+2 == N && j+2 == M) continue;
            if(A > 0){
                res[i][j] = '<';
                res[i][j+1] = '>';
                --A;
                if(A > 0){
                    res[i+1][j] = '<';
                    res[i+1][j+1] = '>';
                    --A;
                }
            } else if(B > 0){
                res[i][j] = '^';
                res[i+1][j] = 'v';
                --B;
                if(B > 0){
                    res[i][j+1] = '^';
                    res[i+1][j+1] = 'v';
                    --B;
                }
            }
        }
    }
    if(A > 0 || B > 0) return vector<string>();
    return res;
}

vector<string> solve(int N, int M, int A, int B){
    {
        auto r = try4(N, M, A, B);
        if(!r.empty()) return r;
    }
    vector<string> res(N, string(M, '.'));
    if(N%2 == 1){
        for(int i=0;i+1<M && A;i+=2){
            res[N-1][i] = '<';
            res[N-1][i+1] = '>';
            --A;
        }
        --N;
    }
    if(M%2 == 1){
        for(int i=0;i+1<N && B;i+=2){
            res[i][M-1] = '^';
            res[i+1][M-1] = 'v';
            --B;
        }
        --M;
    }
    if(2*(A+B) > N*M) return vector<string>();
    for(int i=0;i<N;i+=2){
        for(int j=0;j<M;j+=2){
            if(A > 0){
                res[i][j] = '<';
                res[i][j+1] = '>';
                --A;
                if(A > 0){
                    res[i+1][j] = '<';
                    res[i+1][j+1] = '>';
                    --A;
                }
            } else if(B > 0){
                res[i][j] = '^';
                res[i+1][j] = 'v';
                --B;
                if(B > 0){
                    res[i][j+1] = '^';
                    res[i+1][j+1] = 'v';
                    --B;
                }
            }
        }
    }
    if(A > 0 || B > 0) return vector<string>();
    return res;
}

int main(){
    int N, M, A, B; cin >> N >> M >> A >> B;
    auto res = solve(N, M, A, B);
    cout << (res.empty() ? "NO" : "YES") << endl;
    for(auto& s : res) cout << s << endl;
}
