use proconio::input;

fn main() {
    input! {
        s : String
    };
    let mut dp = [[0i64;2019];2];
    let bytes = s.as_bytes();
    let mut res = 0;
    for i in 0..bytes.len() {
        dp[i%2][0] += 1;
        for j in 0..2019 { dp[1-i%2][j] = 0; }
        for j in 0..2019 {
            dp[1-i%2][(10*j+(bytes[i]-b'0') as usize)%2019] += dp[i%2][j];
        }
        res += dp[1-i%2][0];
    }
    println!("{}", res);
}
