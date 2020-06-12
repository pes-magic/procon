use proconio::input;

const MOD : i64 = 998_244_353;

fn main() {
    input! {
        n : usize,
        s : usize,
        a : [usize; n]
    };
    let mut dp = vec![0; s+1];
    dp[0] = 1;
    for &t in &a {
        for j in (0..=s).rev() {
            if j + t <= s {
                dp[j+t] = (dp[j+t] + dp[j]) % MOD;
            }
            dp[j] = 2 * dp[j] % MOD;
        }
    }
    println!("{}", dp[s]);
}
