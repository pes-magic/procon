use proconio::input;

fn main() {
    input!{
        n: usize,
        a: [u64; n]
    };
    let s = a[2..n].iter().fold(0, |x, y| x^y);
    let mut dp = [[[a[0]; 2]; 2]; 45];
    dp[0][0][0] = 0;
    for i in 0..44 {
        for j in 0..2 {
            for k in 0..2 {
                if dp[i][j][k] == a[0] { continue; }
                let x = a[0] - (j << i) as u64;
                let y = a[1] + (k << i) as u64;
                if ((x^y^s) >> i) % 2 == 1 { continue }
                let x0 = (a[0] >> i) % 2;
                let y0 = (a[1] >> i) % 2;
                for l in 0..2 {
                    if (l << i) as u64 >= x { continue }
                    let nj = if x0 < (j + l) as u64 { 1 } else { 0 };
                    let nk = if y0 + (k + l) as u64 >= 2 { 1 } else { 0 };
                    dp[i+1][nj][nk] = std::cmp::min(dp[i+1][nj][nk], dp[i][j][k] + (l << i) as u64);
                }
            }
        }
    }
    let mut res = a[0];
    for i in 0..2 {
        for j in 0..2 {
            res = std::cmp::min(res, dp[44][i][j]);
        }
    }
    if res < a[0] {
        println!("{}", res);
    } else {
        println!("-1");
    }
}
