use proconio::input;

fn main() {
    input! {
        (n, a, b, c) : (usize, usize, usize, usize),
        s : [String; n]
    };
    let mut dp = vec![[[[(3, 0); 7]; 7]; 7]; n+1];
    dp[0][a.min(6)][b.min(6)][c.min(6)].0 = 0;
    for i in 0..n {
        for ia in 0..=6 {
            for ib in 0..=6 {
                for ic in 0..=6 {
                    if dp[i][ia][ib][ic].0 == 3 { continue; }
                    if s[i] == "AB" {
                        if ib > 0 { dp[i+1][6.min(ia+1)][ib-1][ic] = (0, (ia*7+ib)*7+ic); }
                        if ia > 0 { dp[i+1][ia-1][6.min(ib+1)][ic] = (1, (ia*7+ib)*7+ic); }
                    }
                    if s[i] == "AC" {
                        if ic > 0 { dp[i+1][6.min(ia+1)][ib][ic-1] = (0, (ia*7+ib)*7+ic); }
                        if ia > 0 { dp[i+1][ia-1][ib][6.min(ic+1)] = (2, (ia*7+ib)*7+ic); }
                    }
                    if s[i] == "BC" {
                        if ic > 0 { dp[i+1][ia][6.min(ib+1)][ic-1] = (1, (ia*7+ib)*7+ic); }
                        if ib > 0 { dp[i+1][ia][ib-1][6.min(ic+1)] = (2, (ia*7+ib)*7+ic); }
                    }
                }
            }
        }
    }
    for ia in 0..=6 {
        for ib in 0..=6 {
            for ic in 0..=6 {
                if dp[n][ia][ib][ic].0 != 3 {
                    let mut res = vec![0; n];
                    let mut sa = ia;
                    let mut sb = ib;
                    let mut sc = ic;
                    for i in (0..n).rev() {
                        res[i] = dp[i+1][sa][sb][sc].0;
                        let idx = dp[i+1][sa][sb][sc].1;
                        sa = idx/7/7;
                        sb = idx/7%7;
                        sc = idx%7;
                    }
                    println!("Yes");
                    for t in res { println!("{}", ["A", "B", "C"][t]); }
                    return;
                }
            }
        }
    }
    println!("No");
}
