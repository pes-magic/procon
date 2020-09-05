fn main() {
    proconio::input!{
        n: usize,
        a: [usize; n]
    }
    const MOD : i64 = 998244353;
    let s: usize = a.iter().sum();
    let mut dp = vec![0; s+1];
    let mut dp2 = vec![0; s+1];
    dp[0] = 3;
    dp2[0] = 1;
    for &t in &a {
        for i in (0..=(s-t)).rev() {
            dp[i+t] = (dp[i+t] + dp[i]) % MOD;
            dp[i] = (2 * dp[i]) % MOD;
            dp2[i+t] = (dp2[i+t] + dp2[i]) % MOD;
        }
    }
    let mut res = 1;
    for _ in 0..n { res = 3 * res % MOD }
    for i in (s+1)/2..=s { res = (res + MOD - dp[i]) % MOD }
    if s%2 == 0 { res = (res + 3 * dp2[s/2]) % MOD }
    println!("{}", res);
}
