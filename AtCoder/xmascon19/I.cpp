#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    int H, W;
    while(cin >> H >> W){
        vector<int> line;
        vector<int> paint;
        for(int y=0;y<H;y++){
            string S; cin >> S;
            for(int x=0;x<W;x++){
                if(S[x] == '#') continue;
                paint.push_back(31*y-19*x-18);
            }
        }
        for(int i=0;i<(H+18)/19*19;i++){
            for(int j=0;j<(W+30)/31*31;j++){
                line.push_back(31*i-19*j);
            }
        }
        sort(paint.begin(), paint.end());
        paint.erase(unique(paint.begin(), paint.end()), paint.end());
        sort(line.begin(), line.end());
        line.erase(unique(line.begin(), line.end()), line.end());
        int lineIdx = 0;
        int paintIdx = 0;
        int res = 0;
        while(paintIdx < paint.size()){
            while(lineIdx + 1 < line.size() && line[lineIdx+1] <= paint[paintIdx] + 48) ++lineIdx;
            ++res;
            while(paintIdx < paint.size() && paint[paintIdx] <= line[lineIdx]) ++paintIdx;
        }
        cout << res << endl;
    }
}