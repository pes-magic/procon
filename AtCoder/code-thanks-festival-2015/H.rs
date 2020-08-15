fn main() {
    proconio::input! {
        r : usize,
        c : usize,
        k : i32,
        s : [String; r]
    };
    let mut sum = vec![vec![0; c+1]; r+1];
    let mut cnt = vec![vec![vec![0; c+1]; r+1]; 10];
    for i in 0..r {
        let x = s[i].as_bytes();
        for j in 0..c {
            sum[i+1][j+1] = (x[j]-b'0') as i32 + sum[i+1][j] + sum[i][j+1] - sum[i][j];
            for k in 0..10 {
                cnt[k][i+1][j+1] = (if x[j] - b'0' == k as u8 { 1 } else { 0 }) + cnt[k][i+1][j] + cnt[k][i][j+1] - cnt[k][i][j];
            }
        }
    }
    if k < 8 {
        println!("0");
        return;
    }
    let mut res: i64 = 0;
    for rs in 0..r {
        for re in rs+3..=r {
            let mut idx = 0;
            let mut cur = 0;
            for i in 0..c {
                while idx < c && cur <= k {
                    cur += sum[re][idx+1] - sum[re][idx] - sum[rs][idx+1] + sum[rs][idx];
                    idx += 1;
                }
                if cur <= k { break }
                for j in idx-1..c {
                    let over = cur + (sum[re][j+1] - sum[re][idx] - sum[rs][j+1] + sum[rs][idx]) - k;
                    if over >= 10 { break }
                    if j-i < 2 { continue }
                    let d = &cnt[over as usize];
                    res += d[re-1][j] - d[re-1][i+1] - d[rs+1][j] + d[rs+1][i+1];
                }
                cur -= sum[re][i+1] - sum[re][i] - sum[rs][i+1] + sum[rs][i];
            }
        }
    }
    println!("{}", res);
}
