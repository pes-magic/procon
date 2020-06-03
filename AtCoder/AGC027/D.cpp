#include <iostream>
#include <vector>
#include <deque>

using namespace std;

long long gcd(long long a, long long b){ return a%b ? gcd(b, a%b) : b; }
long long lcm(long long a, long long b){ return a/gcd(a, b)*b; }

int main(){
    deque<int> prime;
    prime.push_back(2);
    prime.push_back(3);
    for(int i=5;prime.size()<1000;i+=2){
        bool ok = true;
        for(auto& t : prime) if(i%t == 0) ok = false;
        if(ok) prime.push_back(i);
    }
    vector<int> p1, p2;
    for(int i=0;i<250;i++){
        p1.push_back(prime.front());
        prime.pop_front();
        p1.push_back(prime.back());
        prime.pop_back();
        p2.push_back(prime.front());
        prime.pop_front();
        p2.push_back(prime.back());
        prime.pop_back();
    }
    vector<vector<long long>> m(500, vector<long long>(500, 1));
    int v = 0;
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            if((i+j)%2) continue;
            m[i][j] = p1[(i+j)/2] * p2[(j-i+498)/2];
            v = max(v, (i+j)/2);
            v = max(v, (j-i+498)/2);
        }
    }
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            if((i+j)%2 == 0) continue;
            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, -1, 0, 1};
            for(int d=0;d<4;d++){
                int nx = i+dx[d];
                int ny = j+dy[d];
                if(nx < 0 || 500 <= nx || ny < 0 || 500 <= ny) continue;
                m[i][j] = lcm(m[i][j], m[nx][ny]);
            }
            ++m[i][j];
        }
    }
    int N; cin >> N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) cout << m[i][j] << " ";
        cout << endl;
    }

}