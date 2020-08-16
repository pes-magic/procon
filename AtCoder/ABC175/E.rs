fn main() {
    proconio::input! {
        r : usize,
        c : usize,
        k : usize,
        item : [(usize, usize, i64); k]
    };
    let mut v = vec![vec![0; c]; r];
    for &p in &item { v[p.0-1][p.1-1] = p.2; }
    let mut dp = vec![vec![vec![0; 4]; c]; r];
    dp[0][0][1] = v[0][0];
    for i in 0..r {
        for j in 0..c {
            for k in 0..=3 {
                if j+1 < c {
                    if k < 3 {
                        dp[i][j+1][k+1] = dp[i][j+1][k+1].max(dp[i][j][k] + v[i][j+1]);
                    }
                    dp[i][j+1][k] = dp[i][j+1][k].max(dp[i][j][k]);
                }
                if i+1 < r {
                    dp[i+1][j][0] = dp[i+1][j][0].max(dp[i][j][k]);
                    dp[i+1][j][1] = dp[i+1][j][1].max(dp[i][j][k] + v[i+1][j]);
                }
            }
        }
    }
    println!("{}", dp[r-1][c-1].iter().max().unwrap());
}
