#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<long long> res(N+1, 0);
    for(int a=0;a<=M;a++){
        long long s0 = a*a;
        for(int b=a;b<=M;b++){
            long long s1 = s0 + (a+b)*b;
            if(s1 > N) break;
            for(int c=b;c<=M;c++){
                long long s2 = s1 + (a+b+c)*c;
                if(s2 > N) break;
                for(int d=c;d<=M;d++){
                    long long s3 = s2 + (a+b+c+d)*d;
                    if(s3 > N) break;
                    if(a == b){
                        if(b == c){
                            if(c == d){
                                res[s3]++;
                            } else {
                                res[s3] += 4;
                            }
                        } else {
                            if(c == d){
                                res[s3] += 6;
                            } else {
                                res[s3] += 12;
                            }
                        }
                    } else {
                        if(b == c){
                            if(c == d){
                                res[s3] += 4;
                            } else {
                                res[s3] += 12;
                            }
                        } else {
                            if(c == d){
                                res[s3] += 12;
                            } else {
                                res[s3] += 24;
                            }
                        }
                    }
                }
            }
        }
    }
    for(auto& t : res) cout << t << endl;
}