fn main() {
    proconio::input! {
        n: usize,
        p: [f64; n]
    }
    let mut dp = vec![0.0; n+1];
    dp[0] = 1.0;
    for &d in &p {
        for i in (0..n).rev() {
            dp[i+1] += dp[i] * d;
            dp[i] *= 1.0 - d;
        }
    }
    let mut res = 0.0;
    for i in (n+1)/2..=n { res += dp[i]; }
    println!("{:.9}", res);
}
