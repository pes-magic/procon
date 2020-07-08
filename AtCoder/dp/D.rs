use proconio::input;

fn main() {
    input! {
        n: usize,
        w: usize,
        v: [(usize, i64); n]
    };
    let mut dp = vec![0; w+1];
    for &p in &v {
        for i in (p.0..=w).rev() {
            dp[i] = dp[i].max(dp[i-p.0] + p.1);
        }
    }
    println!("{}", dp[w]);
}
