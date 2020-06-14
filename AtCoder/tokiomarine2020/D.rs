use proconio::input;

fn calc(start: usize, end: usize, v: &Vec<(i64, i64)>) -> Vec<(i64, i64)> {
    let mut res = Vec::new();
    let mut val = Vec::new();
    let mut idx = start;
    while idx > end {
        val.push(v[idx-1]);
        idx /= 2;
    }
    for i in 0..1<<val.len() {
        let mut sv = 0;
        let mut sw = 0;
        for j in 0..val.len() {
            if i&(1<<j) != 0 {
                sv += val[j].0;
                sw += val[j].1;
            }
        }
        res.push((sw, sv));
    }
    res.sort();
    for i in 1..res.len() {
        res[i].1 = std::cmp::max(res[i].1, res[i-1].1);
    }
    res
}

fn main() {
    input! {
        n : usize,
        v : [(i64, i64); n],
        q : usize,
        query : [(usize, i64); q]
    };
    let thr = 1024;
    let mut first = Vec::new();
    for i in 0..std::cmp::min(thr, n) {
        first.push(calc(i+1, 0, &v));
    }
    for &t in &query {
        let mut res = 0;
        if t.0 <= thr {
            for &r in &first[t.0-1] {
                if r.0 > t.1 { continue }
                res = std::cmp::max(res, r.1);
            }
        } else {
            let second = calc(t.0, thr, &v);
            let mut par = t.0;
            while par > thr { par /= 2; }
            par -= 1;
            let mut idx0 = 0;
            let mut idx1 = second.len() - 1;
            while idx0 < first[par].len() && idx1 < second.len() {
                if first[par][idx0].0 + second[idx1].0 <= t.1 {
                    res = std::cmp::max(res, first[par][idx0].1 + second[idx1].1);
                    idx0 += 1;
                } else {
                    idx1 = idx1.wrapping_add(!0);
                }
            }
        }
        println!("{}", res);
    }
}
