fn main() {
    proconio::input! {
        s : String,
        t : String
    };
    let a = s.as_bytes();
    let b = t.as_bytes();
    let mut dp = vec![vec![0; t.len()+1]; s.len()+1];
    for i in (0..s.len()).rev() {
        for j in (0..t.len()).rev() {
            dp[i][j] = dp[i+1][j+1] + if a[i] == b[j] { 1 } else { 0 };
            dp[i][j] = dp[i][j].max(dp[i][j+1]);
            dp[i][j] = dp[i][j].max(dp[i+1][j]);
        }
    }
    let mut x = 0;
    let mut y = 0;
    while x < s.len() && y < t.len() {
        if a[x] == b[y] && dp[x][y] == dp[x+1][y+1] + 1 {
            print!("{}", a[x] as char);
            x += 1;
            y += 1;
        } else if dp[x][y] == dp[x+1][y+1] {
            x += 1;
            y += 1;
        } else if dp[x][y] == dp[x][y+1] {
            y += 1;
        } else {
            x += 1;
        }
    }
    println!("");
}
