fn main() {
    proconio::input!{
        n: usize,
        k: usize,
        v: [[i64; k]; n]
    }
    let m = 1000000007;
    let mut dp = vec![vec![0; k]; n];
    for i in 0..k { dp[0][i] = 1 }
    for i in 1..n {
        let mut idx = 0;
        let mut sum = 0;
        for j in 0..k {
            while idx < k && v[i-1][idx] <= v[i][j] {
                sum = (sum + dp[i-1][idx]) % m;
                idx += 1;
            }
            dp[i][j] = sum;
        }
    }
    let mut res = 0;
    for i in 0..k { res = (res + dp[n-1][i]) % m }
    println!("{}", res);
}
