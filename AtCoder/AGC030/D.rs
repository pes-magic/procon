use std::io::Read;


fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let q = it.next().unwrap().parse::<usize>().unwrap();
    let a = (0..n).map(|_| it.next().unwrap().parse::<i32>().unwrap()).collect::<Vec<_>>();
    let mut dp = vec![vec![0; n]; n];
    for i in 0..n {
        for j in 0..n {
            if a[i] > a[j] { dp[i][j] = 1 }
        }
    }
    let m : i64 = 1_000_000_007;
    let d2 = m - m/2;
    for _ in 0..q {
        let x = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let y = it.next().unwrap().parse::<usize>().unwrap() - 1;
        for i in 0..n {
            if i == x || i == y { continue }
            let avg1 = d2 * (dp[i][x] + dp[i][y]) % m;
            let avg2 = d2 * (dp[x][i] + dp[y][i]) % m;
            dp[i][x] = avg1;
            dp[i][y] = avg1;
            dp[x][i] = avg2;
            dp[y][i] = avg2;
        }
        let avg = d2 * (dp[x][y] + dp[y][x]) % m;
        dp[x][y] = avg;
        dp[y][x] = avg;
    }
    let mut res = 0;
    for i in 0..n {
        for j in i..n {
            res = (res + dp[i][j]) % m;
        }
    }
    for _ in 0..q { res = 2 * res % m }
    println!("{}", res);
}
