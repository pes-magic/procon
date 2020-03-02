// 円
// verifyed
// https://atcoder.jp/contests/abc157/tasks/abc157_f

using P = complex<double>;
using Circle = pair<P,double>;

const double EPS = 1e-12;

// not verifyed
bool overlap(const Circle& c1, const Circle& c2){
	auto d = abs(c1.first - c2.first);
	return c2.second - (d + c1.second) > -EPS;
}

bool inCircle(const Circle& c, const P& p){
	return c.second - abs(c.first-p) > -EPS;
}

bool crossCircle(const Circle& c1, const Circle& c2){
	auto r1 = c1.second;
	auto r2 = c2.second;
	auto d = abs(c1.first-c2.first);
	if(d < r1 || d < r2) return d - abs(r1 - r2) > EPS;
	return r1 + r2 - d > -EPS;
}

vector<P> crossPoint(const Circle& c1, const Circle& c2){
    if(!crossCircle(c1, c2)) return vector<P>();
	auto r1 = c1.second;
	auto r2 = c2.second;
	auto r3 = abs(c1.first - c2.first);
	auto rc = (r3*r3 + r1*r1 - r2*r2) / (2*r3);
	auto rs = sqrt(r1*r1 - rc*rc);
	P dif = (c2.first-c1.first)/r3;
    vector<P> res;
    res.emplace_back(c1.first + dif * P(rc,rs));
    res.emplace_back(c1.first + dif * P(rc,-rs));
	return res;
}
