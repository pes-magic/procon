// Zalgorithm
// Verifyed
// https://atcoder.jp/contests/abc150/tasks/abc150_f

vector<int> Zalgorithm(auto S){
    vector<int> res(S.size());
    res[0] = S.size();
    int i = 1, j = 0;
    while (i < S.size()) {
        while (i+j < S.size() && S[j] == S[i+j]) ++j;
        res[i] = j;
        if (j == 0) { ++i; continue;}
        int k = 1;
        while (i+k < S.size() && k+res[k] < j) res[i+k] = res[k], ++k;
        i += k; j -= k;
    }
    return res;
}