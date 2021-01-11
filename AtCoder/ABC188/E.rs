const INF : i64 = 1 << 60;

fn main() {
    proconio::input! {
        n: usize,
        m: usize,
        a: [i64; n],
        edge: [(proconio::marker::Usize1, proconio::marker::Usize1); m]
    }
    let mut g = vec![Vec::new(); n];
    for &e in &edge { g[e.0].push(e.1) }
    let mut buy = vec![INF; n];
    let mut res = -INF;
    for i in 0..n {
        res = res.max(a[i] - buy[i]);
        buy[i] = buy[i].min(a[i]);
        for &e in &g[i] { buy[e] = buy[e].min(buy[i]); }
    }
    println!("{}", res);
}
