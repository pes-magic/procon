// 接尾辞配列 (Larsson-Sadakane法)
// Verifyed
// https://atcoder.jp/contests/arc050/tasks/arc050_d
// https://atcoder.jp/contests/ddcc2020-final/tasks/ddcc2020_final_c

vector<int> getSuffixArray(const auto& str, int alphabetSize){
	const int n = str.size();
	vector<pair<int, int>> vp(n);
	vector<int> rank(n), cnt(alphabetSize, 0);
	for(int i=0;i<n;i++) cnt[str[i]]++;
	for(int i=1;i<alphabetSize;i++) cnt[i] += cnt[i-1];
	for(int i=0;i<n;i++){
		rank[i] = vp[i].first = cnt[str[i]];
		vp[i].second = i;
	}
	sort(vp.begin(), vp.end());
	for(int h=1;h<n;h*=2){
		auto cur = vp.begin();
		while(cur != vp.end()){
			auto end = cur;
			int key = rank[cur->second];
			while(end != vp.end() && rank[end->second] == key){
				end->first = end->second + h < n ? rank[end->second + h] : -1;
				end++;
			}
			int s = distance(vp.begin(), cur), e = distance(vp.begin(), end);
			if(e - s > 1){
				sort(cur, end);
				rank[vp[e-1].second] = key;
				for(int i=e-2;i>=s;i--){
					rank[vp[i].second] = (vp[i].first == vp[i+1].first ? rank[vp[i+1].second] : key - (e-1-i));
				}
			}
			cur = end;
		}
	}
    vector<int> res(n);
	for(int i=0;i<n;i++) res[i] = vp[i].second;
    return res;
}

vector<int> getHeightArray(const vector<int> &SA, const auto &str){
	int n = SA.size();
	vector<int> rev(n);
	for(int i=0;i<n;i++) rev[SA[i]] = i;
    vector<int> res(n, 0);
	int prev = 0;
	for(int i=0;i<n;i++){
		int idx = rev[i];
		if(idx == n-1){ res[idx] = prev = 0; continue; }
		idx = SA[idx+1];
		int t = prev;
		while(max(i, idx)+t < n && str[i+t] == str[idx+t]) t++;
		res[rev[i]] = t;
		prev = max(0, t-1);
	}
    return res;
}