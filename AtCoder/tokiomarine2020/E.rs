use proconio::input;

fn main() {
    input! {
        n: usize,
        k: usize,
        s: usize,
        t: usize,
        a: [usize; n]
    };
    let b = a.iter().filter(|&v| v&s == s && v|t == t ).map(|&v| v^s).collect::<Vec<usize>>();
    let mut comb = [[0 as i64; 51]; 51];
    let mut valid = [0; 51];
    for i in 1..=50 {
        comb[i][0] = 1;
        for j in 1..i {
            comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
        }
        comb[i][i] = 1;
        for j in 1..=std::cmp::min(i, k) {
            valid[i] += comb[i][j];
        }
    }
    let mut res = valid[b.len()];
    let mut cnt = [0; 1<<18];
    let mask = t^s;
    for i in 1..1<<18 {
        if i|mask != mask { continue }
        let sgn = if i.count_ones()%2 == 1 { -1 } else { 1 };
        for &v in &b { cnt[v&i] += 1; }
        for &v in &b {
            if cnt[v&i] == 0 { continue }
            res += sgn * valid[cnt[v&i]];
            cnt[v&i] = 0;
        }
    }
    println!("{}", res);
}
