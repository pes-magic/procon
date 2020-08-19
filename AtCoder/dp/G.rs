use std::collections::VecDeque;

fn main() {
    proconio::input! {
        n: usize,
        m: usize,
        edge: [(usize, usize); m]
    };
    let mut dp= vec![0; n];
    let mut cnt = vec![0; n];
    let mut g = vec![Vec::new(); n];
    for &e in &edge {
        cnt[e.0-1] += 1;
        g[e.1-1].push(e.0-1);
    }
    let mut qu = VecDeque::new();
    for i in 0..n {
        if cnt[i] == 0 { qu.push_back(i); }
    }
    while !qu.is_empty() {
        let p = qu.pop_front().unwrap();
        for &next in &g[p] {
            dp[next] = dp[next].max(dp[p]+1);
            cnt[next] -= 1;
            if cnt[next] == 0 { qu.push_back(next); }
        }
    }
    println!("{}", dp.iter().max().unwrap());
}
