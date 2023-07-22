use proconio::input;
use proconio::marker::Chars;

const MOD: i64 = 998244353;

fn main() {
    input! {
        n: usize,
        t: Chars
    }
    let mut pad = vec![vec![0; 2 * n + 1]; 2];
    let mut dp = vec![vec![0; 2 * n + 1]; 2];
    pad[0][n] = 1;
    for i in 0..2 * n {
        for c in 0..=2 * n {
            if pad[i % 2][c] == 0 {
                continue;
            }
            if t[i] == '+' || t[i] == '?' {
                if c + 1 <= 2 * n {
                    let add = if c + 1 >= n { c + 1 - n } else { n - (c + 1) };
                    dp[(i + 1) % 2][c + 1] += dp[i % 2][c] + pad[i % 2][c] * (add as i64);
                    dp[(i + 1) % 2][c + 1] %= MOD;
                    pad[(i + 1) % 2][c + 1] += pad[i % 2][c];
                    pad[(i + 1) % 2][c + 1] %= MOD;
                }
            }
            if t[i] == '-' || t[i] == '?' {
                if c >= 1 {
                    let add = if c - 1 >= n { c - 1 - n } else { n - (c - 1) };
                    dp[(i + 1) % 2][c - 1] += dp[i % 2][c] + pad[i % 2][c] * (add as i64);
                    dp[(i + 1) % 2][c - 1] %= MOD;
                    pad[(i + 1) % 2][c - 1] += pad[i % 2][c];
                    pad[(i + 1) % 2][c - 1] %= MOD;
                }
            }
            dp[i % 2][c] = 0;
            pad[i % 2][c] = 0;
        }
    }
    println!("{}", dp[0][n]);
}
