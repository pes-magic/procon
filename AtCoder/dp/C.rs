use proconio::input;

fn main() {
    input! {
        n: usize,
        h: [(i32, i32, i32); n]
    };
    let mut dp = vec![[0; 3]; n];
    dp[0][0] = h[0].0;
    dp[0][1] = h[0].1;
    dp[0][2] = h[0].2;
    for i in 1..n {
        dp[i][0] = dp[i-1][1].max(dp[i-1][2]) + h[i].0;
        dp[i][1] = dp[i-1][2].max(dp[i-1][0]) + h[i].1;
        dp[i][2] = dp[i-1][0].max(dp[i-1][1]) + h[i].2;
    }
    println!("{}", dp[n-1].iter().max().unwrap());
}
