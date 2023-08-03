use proconio::input;
use proconio::marker::Chars;

fn valid(s: &Vec<char>, r: &Vec<char>, b: &Vec<char>) -> i64 {
    let mut dp = vec![vec![0; b.len() + 1]; r.len() + 1];
    dp[0][0] = 1;
    for i in 0..=r.len() {
        for j in 0..=b.len() {
            if i < r.len() && r[i] == s[i + j] {
                dp[i + 1][j] += dp[i][j];
            }
            if j < b.len() && b[j] == s[i + j] {
                dp[i][j + 1] += dp[i][j];
            }
        }
    }
    dp[r.len()][b.len()]
}

fn main() {
    input! { n: usize, s: Chars}
    let t = (0..n).map(|i| s[2 * n - 1 - i]).collect();
    let mut res = 0;
    for i in 0..1 << n {
        let mut r = Vec::new();
        let mut b = Vec::new();
        for j in 0..n {
            if i & (1 << j) != 0 {
                r.push(s[j]);
            } else {
                b.push(s[j])
            };
        }
        res += valid(&t, &r, &b);
    }
    println!("{}", res);
}
