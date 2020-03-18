#include <iostream>
#include <vector>
#include <string>

using namespace std;

uint32_t xorshift(void) {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13); y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

bool valid(vector<vector<int>>& board){
    const int N = board.size();
    for(int i=0;i<N;i++){
        vector<int> use(N*N, 0);
        int cnt = 0;
        for(int j=0;j<N;j++){
            if(board[i][j] == -1) continue;
            if(use[board[i][j]]) continue;
            use[board[i][j]] = 1;
            ++cnt;
        }
        if(cnt != 3) return false;
    }
    for(int j=0;j<N;j++){
        vector<int> use(N*N, 0);
        int cnt = 0;
        for(int i=0;i<N;i++){
            if(board[i][j] == -1) continue;
            if(use[board[i][j]]) continue;
            use[board[i][j]] = 1;
            ++cnt;
        }
        if(cnt != 3) return false;
    }
    return true;
}

vector<vector<int>> find(int N){
    while(true){
        vector<vector<int>> board(N, vector<int>(N, -1));
        for(int i=0;i<2*N;i++){
            int err = 0;
            while(err++ < 100){
                int x = xorshift()%N;
                int y = xorshift()%N;
                int dx = xorshift()%2;
                int dy = 1 - dx;
                if(x + dx >= N) continue;
                if(y + dy >= N) continue;
                if(board[x][y] != -1) continue;
                if(board[x+dx][y+dy] != -1) continue;
                board[x][y] = board[x+dx][y+dy] = i;
                break;
            }
        }
        if(valid(board)){
            return board;
        }
    }
}

int main(){
    // for(int i=4;i<=7;i++){
    //     auto board = find(i);
    //     cout << "string res" << i << "[] = {" << endl;
    //     auto chr = [](int t) -> char {
    //         return t < 0 ? '.' : 'a' + t;
    //     };
    //     for(auto& v : board){
    //         cout << "    \"";
    //         for(auto& c : v) cout << (char)chr(c);
    //         cout << "\"," << endl;
    //     }
    //     cout << "};" << endl;
    // }
    int N;
    while(cin >> N){
        if(N == 2){
            cout << -1 << endl;
        } else if(N == 3){
            cout << "aab" << endl;
            cout << "b.b" << endl;
            cout << "baa" << endl;
        } else {
            vector<string> vs(N, string(N, '.'));
            string res4[] = {
                "gghe",
                "ddhe",
                "fcbb",
                "fcaa",
            };
            string res5[] = {
                "ee.bc",
                "..abc",
                "hhajj",
                "dff.g",
                "d.iig",
            };
            string res6[] = {
                ".d.aae",
                "id...e",
                "i.kff.",
                "j.k..g",
                "jcc..g",
                "bbllhh",
            };
            string res7[] = {
                "llm.ee.",
                "..mh..f",
                ".aah..f",
                "ii...jb",
                "g....jb",
                "g..kk.d",
                "..ccnnd",
            };
            int s = 0;
            if(N%4 == 1){
                for(int i=0;i<5;i++){
                    for(int j=0;j<5;j++){
                        vs[i][j] = res5[i][j];
                    }
                }
                s = 5;
            }
            if(N%4 == 2){
                for(int i=0;i<6;i++){
                    for(int j=0;j<6;j++){
                        vs[i][j] = res6[i][j];
                    }
                }
                s = 6;
            }
            if(N%4 == 3){
                for(int i=0;i<7;i++){
                    for(int j=0;j<7;j++){
                        vs[i][j] = res7[i][j];
                    }
                }
                s = 7;
            }
            for(;s<N;s+=4){
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        vs[s+i][s+j] = res4[i][j];
                    }
                }
            }
            for(auto& s : vs) cout << s << endl;
        }
    }
}