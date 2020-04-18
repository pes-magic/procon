use proconio::input;
use std::cmp;

fn main() {
    input! {
        n : usize,
        a : [i64; n]
    };
    let mut dp = vec![[-(1 << 50); 3]; n];
    for i in 0..cmp::min(n, 3) {
        dp[i][i] = a[i];
    }
    for i in 0..n {
        for j in 0..3 {
            for k in 0..3 {
                if i+k+2 >= n || j+k >= 3 { break;}
                dp[i+k+2][j+k] = cmp::max(dp[i+k+2][j+k], dp[i][j] + a[i+k+2]);
            }
        }
    }
    let res = if n%2 == 1 {
        cmp::max(dp[n-1][2], cmp::max(dp[n-2][1], dp[n-3][0]))
    } else {
        cmp::max(dp[n-1][1], dp[n-2][0])
    };
    println!("{}", res);
}
