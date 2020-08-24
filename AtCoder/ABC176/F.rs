fn main() {
    proconio::input! {
        n: usize,
        a1: proconio::marker::Usize1,
        a2: proconio::marker::Usize1,
        a: [(proconio::marker::Usize1, proconio::marker::Usize1, proconio::marker::Usize1); n-1],
        an: proconio::marker::Usize1
    };
    let mut dp = vec![vec![-1; n]; n];
    let mut line = vec![-1; n];
    let mut all = 0;
    let mut plus = 0;
    dp[a1][a2] = 0;
    dp[a2][a1] = 0;
    line[a1] = 0;
    line[a2] = 0;
    for &p in &a {
        if p.0 == p.1 && p.1 == p.2 {
            plus += 1;
            continue;
        }
        let mut update = Vec::new();
        update.push((p.1, p.2, all.max(dp[p.0][p.0] + 1)));
        update.push((p.2, p.0, all.max(dp[p.1][p.1] + 1)));
        update.push((p.0, p.1, all.max(dp[p.2][p.2] + 1)));
        for i in 0..n {
            if dp[i][p.1] != -1 && p.1 == p.2 {
                update.push((i, p.0, dp[i][p.1] + 1));
            }
            if dp[i][p.2] != -1 && p.2 == p.0 {
                update.push((i, p.1, dp[i][p.2] + 1));
            }
            if dp[i][p.0] != -1 && p.0 == p.1 {
                update.push((i, p.2, dp[i][p.0] + 1));
            }
            if line[i] != -1 {
                update.push((i, p.0, line[i]));
                update.push((i, p.1, line[i]));
                update.push((i, p.2, line[i]));
            }
        }
        for &u in &update {
            dp[u.0][u.1] = dp[u.0][u.1].max(u.2);
            dp[u.1][u.0] = dp[u.1][u.0].max(u.2);
            line[u.0] = line[u.0].max(u.2);
            line[u.1] = line[u.1].max(u.2);
            all = all.max(u.2);
        }
    }
    let mut res = 0;
    for i in 0..n {
        for j in 0..n {
            res = res.max(dp[i][j] + plus + if i == j && i == an { 1 } else { 0 });
        }
    }
    println!("{}", res);
}
