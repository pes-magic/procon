use proconio::input;

const MOD: i64 = 998244353;

fn main() {
    input! { n: usize, m: usize }
    if n <= 2 {
        println!("{}", n);
        return;
    }
    let mut comp = vec![vec![1; 500]; 500];
    for i in 2..500 {
        for j in 1..i {
            comp[i][j] = (comp[i - 1][j] + comp[i - 1][j - 1]) % MOD;
        }
    }
    let mut dp = vec![vec![vec![0; n]; 500]; n + 1];
    dp[2][0][1] = 1;
    dp[2][1][1] = 1;
    for i in 2..n {
        for j in 0..=i * (i - 1) / 2 {
            for k in 1..i {
                let k2 = i - k;
                for l in 0..=k {
                    dp[i + 1][j + l][k + 1] += dp[i][j][k] * comp[k][l];
                    dp[i + 1][j + l][k + 1] %= MOD;
                }
                for l in 0..=k2 {
                    dp[i + 1][j + l + k][k] += dp[i][j][k] * comp[k2][l];
                    dp[i + 1][j + l + k][k] %= MOD;
                }
            }
            dp[i + 1][j][1] += comp[i * (i - 1) / 2][j];
            dp[i + 1][j][1] %= MOD;
            dp[i + 1][j + i][i] += comp[i * (i - 1) / 2][j];
            dp[i + 1][j + i][i] %= MOD;
        }
    }
    println!(
        "{}",
        (dp[n][m].iter().sum::<i64>() + comp[n * (n - 1) / 2][m]) % MOD
    );
}
