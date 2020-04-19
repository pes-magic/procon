use std::collections::BinaryHeap;
use std::cmp;
use num::abs;
use proconio::input;

fn main() {
    input! {
        n : usize,
        a : [i64; n]
    };
    let mut qu = BinaryHeap::new();
    for i in 0..n {
        qu.push((a[i], i));
    }
    let mut dp = vec!(vec!(0; n+1); n+1);
    for i in 0..n {
        let (v, b) = qu.pop().unwrap();
        for j in 0..n {
            if j + n - i > n {
                break;
            }
            dp[j][j+n-i-1] = cmp::max(dp[j][j+n-i-1], dp[j][j+n-i] + v * abs((j+n-i-1) as i64 - b as i64));
            dp[j+1][j+n-i] = cmp::max(dp[j+1][j+n-i], dp[j][j+n-i] + v * abs(j as i64 - b as i64));
        }
    }
    let mut res = 0;
    for i in 0..=n {
        res = cmp::max(res, dp[i][i]);
    }
    println!("{}", res);
}
