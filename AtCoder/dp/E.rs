use proconio::input;

fn main() {
    input! {
        n: usize,
        w: i64,
        v: [(i64, usize); n]
    };
    let mut dp = [w+1; 100001];
    dp[0] = 0;
    for &p in &v {
        for i in (p.1..=100000).rev() {
            dp[i] = dp[i].min(dp[i-p.1] + p.0);
        }
    }
    for i in (0..=100000).rev() {
        if dp[i] <= w {
            println!("{}", i);
            break;
        }
    }
}
