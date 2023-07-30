use proconio::input;

const MOD: i64 = 1000000007;
fn main() {
    input! {n:usize, m:usize}
    let mut dp = vec![vec![vec![0; n + 1]; 2]; 2];
    dp[0][1][0] = 1;
    for i in 1..=n {
        dp[0][0][i] = 1;
    }
    for i in 0..m {
        let src = i % 2;
        let dst = 1 - src;
        for j in 0..=n {
            dp[dst][0][j] = 0;
            dp[dst][1][j] = 0;
        }
        for flg in 0..=1 {
            for num in 0..=n {
                if dp[src][flg][num] == 0 {
                    continue;
                }
                // red
                if num >= 1 {
                    let nflg = if flg == 1 || num == 1 { 1 } else { 0 };
                    for d in 0..=1 {
                        dp[dst][nflg][num - d] += dp[src][flg][num];
                        dp[dst][nflg][num - d] %= MOD;
                    }
                }
                // blue
                if num <= n - 1 {
                    for d in 0..=1 {
                        dp[dst][flg][num + d] += dp[src][flg][num];
                        dp[dst][flg][num + d] %= MOD;
                    }
                }
            }
        }
    }
    println!("{}", dp[m % 2][1].iter().sum::<i64>() % MOD);
}
