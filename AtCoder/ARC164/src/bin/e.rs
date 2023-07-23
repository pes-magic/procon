use itertools::{enumerate, Itertools};
use proconio::input;
use proconio::marker::Usize1;
use std::collections::HashSet;

fn main() {
    input! {
        n: usize, q:usize,
        r: [(Usize1, usize); q]
    }
    let mut segs = HashSet::new();
    segs.insert(0);
    segs.insert(n);
    for &(a, b) in &r {
        segs.insert(a);
        segs.insert(b);
    }
    let mut seg = segs.into_iter().collect_vec();
    seg.sort();
    let mut idx = vec![0; n + 1];
    for (i, value) in enumerate(seg) {
        idx[value] = i;
    }
    let mut add_left = vec![0; n];
    let mut add_right = vec![0; n];
    let mut add = vec![0; n];
    for &(a, b) in &r {
        if a == 0 && b == n {
            continue;
        }
        let idx_a = idx[a];
        let idx_b = idx[b];
        if idx_a + 1 == idx_b {
            add[idx_a] += 1;
        } else {
            add_right[idx_a] += 1;
            add_left[idx_b - 1] += 1;
        }
    }
    if idx[n] == 1 {
        println!("{} {}", 0, q);
        return;
    }
    let mut d = 0;
    while 1 << (d + 1) < idx[n] {
        d += 1;
    }
    let mut dp = vec![vec![1000000000; (1 << d) + 1]; idx[n] - (1 << d) + 1];
    dp[0][0] = 0;
    for i in 0..=(idx[n] - (1 << d)) as usize {
        for j in 0..(1 << d) as usize {
            dp[i][j + 1] = dp[i][j + 1].min(dp[i][j]);
            if i + 1 < dp.len() {
                dp[i + 1][j + 1] = dp[i + 1][j + 1].min(
                    dp[i][j] + add[i + j] + add[i + j + 1] + add_left[i + j] + add_right[i + j + 1],
                );
            }
        }
    }
    println!("{} {}", d + 1, 2 * dp[dp.len() - 1][dp[0].len() - 1]);
}
