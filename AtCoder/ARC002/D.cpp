#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main(){
    int H, W; cin >> H >> W;
    priority_queue<pair<int, pair<int, int>>> qu;
    const int INF = 10000000;
    int wo = INF;
    int wx = INF;
    int sumo = 0;
    int sumx = 0;
    for(int i=0;i<H;i++){
        string S; cin >> S;
        char prev = '-';
        int sizeo = 0;
        int sizex = 0;
        int topx = 0;
        int prevPos = -1;
        int interval = 0;
        for(int j=0;j<W;j++){
            if(prev == '-'){
                if(S[j] == 'x'){ wx = min(wx, j); }
                if(S[j] == 'o'){
                    sizeo = 1;
                    sizex = 0;
                }
            } else if(prev == 'o'){
                if(S[j] == 'o'){
                    sumo += sizeo * (j - prevPos - 1);
                    ++sizeo;
                }
                if(S[j] == 'x'){
                    interval = j - prevPos - 2;
                    sizex = 1;
                    topx = j;
                }
            } else if(prev == 'x'){
                if(S[j] == 'o'){
                    for(int k=0;k<interval;k++) qu.emplace(sizeo+sizex-2, make_pair(sizeo-1, sizex-1));
                    sizeo = 1;
                    sizex = 0;
                } else if(S[j] == 'x'){
                    sumx += (j - topx - sizex);
                    ++sizex;
                }
            }
            if(S[j] != '.'){
                prev = S[j];
                prevPos = j;
            }
        }
        if(prev == 'x'){
            for(int k=0;k<interval;k++) qu.emplace(sizeo+sizex-2, make_pair(sizeo-1, sizex-1));
        } else if(prev == 'o'){
            wo = min(wo, W-1-prevPos);
        }
    }
    if(wo != INF || wx != INF){
        if(wo <= wx){
            cout << "o" << endl;
        } else {
            cout << "x" << endl;
        }
        return 0;
    }
    int offset = qu.size()%2;
    while(!qu.empty()){
        sumo += qu.top().second.first; qu.pop();
        if(qu.empty()) break;
        sumx += qu.top().second.second; qu.pop();
    }
    if(offset == 0){
        if(sumo > sumx){
            cout << "o" << endl;
        } else {
            cout << "x" << endl;
        }
    } else {
        if(sumx > sumo){
            cout << "x" << endl;
        } else {
            cout << "o" << endl;
        }
    }

}