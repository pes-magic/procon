use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let s = it.next().unwrap().as_bytes();
    let n = s.len();
    let k = it.next().unwrap().parse::<usize>().unwrap();
    let mut dp = vec![vec![vec![0; n]; n]; k+1];
    for d in (1..n).rev() {
        for i in 0..k+1 {
            for j in 0..n-d {
                dp[i][j+1][j+d] = std::cmp::max(dp[i][j+1][j+d], dp[i][j][j+d]);
                dp[i][j][j+d-1] = std::cmp::max(dp[i][j][j+d-1], dp[i][j][j+d]);
                let next_i = i + if s[j] == s[j+d] { 0 } else { 1 };
                if next_i > k { continue; }
                dp[next_i][j+1][j+d-1] = std::cmp::max(dp[next_i][j+1][j+d-1], dp[i][j][j+d] + 2);
            }
        }
    }
    let mut res = 0;
    for i in 0..k+1 {
        for j in 0..n {
            for l in 0..n {
                res = std::cmp::max(res, dp[i][j][l] + if j == l { 1 } else { 0 });
            }
        }
    }
    println!("{}", res);
}
