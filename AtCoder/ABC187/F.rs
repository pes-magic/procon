const MOD : i64 = 1000000007;

fn main() {
    proconio::input! {
        n: usize,
        m: usize,
        edge: [(proconio::marker::Usize1, proconio::marker::Usize1); m]
    }
    let mut mask = vec![0; n];
    for &e in &edge {
        mask[e.0] |= 1 << e.1;
        mask[e.1] |= 1 << e.0;
    }
    let mut dp = vec![0; 1<<n];
    let mut res = vec![0; n];
    for i in 0..(1<<n) {
        for j in 0..n {
            if (i>>j)%2 == 1 { continue }
            dp[i|(1<<j)] = (dp[i] + dp[i&mask[j]] + 1) % MOD;
        }
        let sgn = (n - (i.count_ones()) as usize) % 2;
        let mut val = dp[i];
        for j in 0..n {
            if sgn == 0 {
                res[j] = (res[j] + val) % MOD;
            } else {
                res[j] = (res[j] + MOD - val) % MOD;
            }
            val = (val * dp[i]) % MOD;
        }
    }
    for i in 0..n {
        if res[i] != 0 {
            println!("{}", i+1);
            break
        }
    }
}
