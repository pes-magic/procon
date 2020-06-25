use proconio::input;

const MOD : i64 = 998244353;

fn solve(a: usize, b: usize, c: usize, d: usize) -> i64 {
    let mut dp = vec![vec![[0; 2]; d + 1]; c + 1];
    dp[a][b][1] = 1;
    for i in a..=c {
        for j in b..=d {
            if i+1 <= c {
                dp[i+1][j][1] = (dp[i+1][j][1] + dp[i][j][1] * j as i64) % MOD;
                dp[i+1][j][1] = (dp[i+1][j][1] + dp[i][j][0]) % MOD;
            }
            if j+1 <= d {
                dp[i][j+1][0] = (dp[i][j+1][0] + (dp[i][j][0] + dp[i][j][1]) * i as i64) % MOD;
            }
        }
    }
    (dp[c][d][0] + dp[c][d][1]) % MOD
}

fn main() {
    input! {
        a : usize,
        b : usize,
        c : usize,
        d : usize
    };
    println!("{}", solve(a, b, c, d));
}
