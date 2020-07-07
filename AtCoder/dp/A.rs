use proconio::input;

fn main() {
    input! {
        n: usize,
        h: [i32; n]
    };
    let mut dp = vec![1<<30; n];
    dp[0] = 0;
    for i in 1..n {
        dp[i] = dp[i].min(dp[i-1] + (h[i]-h[i-1]).abs());
        if i >= 2 {
            dp[i] = dp[i].min(dp[i-2] + (h[i]-h[i-2]).abs());
        }
    }
    println!("{}", dp[n-1]);
}
