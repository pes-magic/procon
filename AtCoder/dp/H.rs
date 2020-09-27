fn main() {
    proconio::input!{
        h: usize,
        w: usize,
        a: [String; h]
    };
    let mut dp = vec![vec![0; w]; h];
    dp[0][0] = 1;
    let m = 1000000007;
    for i in 0..h {
        for j in 0..w {
            if a[i].as_bytes()[j] == b'#' { continue }
            if i+1 < h && a[i+1].as_bytes()[j] == b'.' {
                dp[i+1][j] = (dp[i][j] + dp[i+1][j]) % m;
            }
            if j+1 < w && a[i].as_bytes()[j+1] == b'.' {
                dp[i][j+1] = (dp[i][j] + dp[i][j+1]) % m;
            }
        }
    }
    println!("{}", dp[h-1][w-1]);
}
