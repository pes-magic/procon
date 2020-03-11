// 最長増加部分列
// Verifyed
// https://atcoder.jp/contests/agc019/tasks/agc019_c

template<typename T>
int LIS(const vector<T>& v){
    if(v.empty()) return 0;
	vector<T> a(v.size(), v[0]);
    auto end = a.begin();
    ++end;
	for(int i=1;i<v.size();i++){
		auto l = lower_bound(a.begin(), end, v[i]);
        if(l == end) ++end;
        *l = v[i];
	}
	return distance(a.begin(), end);
}
