#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool solve(vector<string>& board, int p, vector<int>& row, vector<int>& col, int ch){
    const int N = board.size();
    if(p == N*N){
        bool ok = true;
        for(int i=0;i<N;i++) if(row[i] != 3 || col[i] != 3) ok = false;
        return ok;
    }
    int x = p/N, y = p%N;
    if(y != N-1 || row[x] == 3) if(solve(board, p+1, row, col, ch)) return true;
    if(y+1 < N && board[x][y] == '.' && board[x][y+1] == '.'){
        board[x][y] = board[x][y+1] = 'a'+ch;
        row[x]++;
        col[y]++;
        col[y+1]++;
        if(row[x] <= 3 && col[y] <= 3 && col[y+1] <= 3) if(solve(board, p+2, row, col, ch+1)) return true;
        board[x][y] = board[x][y+1] = '.';
        row[x]--;
        col[y]--;
        col[y+1]--;
    }
    if(x+1 < N && board[x][y] == '.' && board[x+1][y] == '.'){
        board[x][y] = board[x+1][y] = 'a' + ch;
        row[x]++;
        row[x+1]++;
        col[y]++;
        if(row[x] <= 3 && row[x+1] <= 3 && col[y] <= 3) if(solve(board, p+1, row, col, ch+1)) return true;
        board[x][y] = board[x+1][y] = '.';
        row[x]--;
        row[x+1]--;
        col[y]--;
    }
    return false;
}

vector<string> search(int N){
    vector<string> res(N, string(N, '.'));
    vector<int> row(N, 0), col(N, 0);
    solve(res, 0, row, col, 0);
    return res;
}

int main(){
    int N; cin >> N;
    if(N < 3){
        cout << -1 << endl;
        return 0;
    }
    if(N == 3){
        cout << "aab" << endl;
        cout << "b.b" << endl;
        cout << "baa" << endl;
        return 0;
    }
    vector<string> vs(N, string(N, '.'));
    int idx = 0;
    if(N%4==1){
        string a5[] = {
            "..abc",
            "..abc",
            "ddeef",
            "ggh.f",
            "iihjj"
        };
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                vs[i][j] = a5[i][j];
            }
        }
        idx = 5;
    }
    if(N%4==2){
        string a6[] = {
            "...abc",
            "...abc",
            "ddee.f",
            "..gghf",
            "iij.h.",
            "kkj.ll"
        };
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                vs[i][j] = a6[i][j];
            }
        }
        idx = 6;
    }
    if(N%4==3){
        string a7[] = {
            "....abc",
            "....abc",
            "....def",
            "....def",
            "gghh..i",
            "jjkk..i",
            "llmmnn."
        };
        for(int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                vs[i][j] = a7[i][j];
            }
        }
        idx = 7;
    }
    while(idx < N){
        string a4[] = {
            "aabc",
            "ddbc",
            "efgg",
            "efhh"
        };
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                vs[idx+i][idx+j] = a4[i][j];
            }
        }
        idx += 4;
    }
    for(auto& s : vs) cout << s << endl;
}