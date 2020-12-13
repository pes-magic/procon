const INF : i64 = 1 << 60;

fn main() {
    proconio::input! {
        n: usize,
        k: usize,
        h: [i64; n]
    }
    let mut dp = vec![vec![vec![INF; k+1]; n]; n];
    dp[0][n-1][0] = h[0];
    if k > 0 { dp[0][0][1] = 0; }
    for pos in 0..n-1 {
        for last in 0..n {
            for op in 0..=k {
                if dp[pos][last][op] == INF { continue }
                let pre = if last > 0 { h[pos.min(last-1)] } else { 0 };
                dp[pos+1][n-1][op] = dp[pos+1][n-1][op].min(dp[pos][last][op] + (h[pos+1]-pre).max(0));
                if op+1 <= k {
                    let nextlast = last.min(pos+1);
                    dp[pos+1][nextlast][op+1] = dp[pos+1][nextlast][op+1].min(dp[pos][last][op]);
                }
            }
        }
    }
    let mut res = INF;
    for i in 0..n { res = res.min(dp[n-1][i][k]) }
    println!("{}", res);
}
