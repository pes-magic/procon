fn main() {
    proconio::input!{
        h: usize,
        w: usize,
        k: i64,
        v: i64,
        a: [[i64; w]; h]
    };
    let mut sum = vec![vec![0; w+1]; h+1];
    for i in 0..h {
        for j in 0..w {
            sum[i+1][j+1] = a[i][j] + sum[i][j+1] + sum[i+1][j] - sum[i][j];
        }
    }
    let mut res = 0;
    for is in 0..h {
        for ie in is+1..=h {
            let id = (ie - is) as i64;
            for js in 0..w {
                for je in js+1..=w {
                    let jd = (je - js) as i64;
                    let s = sum[ie][je] - sum[is][je] - sum[ie][js] + sum[is][js] + id * jd * k;
                    if s <= v { res = res.max(id*jd) }
                }
            }

        }
    }
    println!("{}", res);
}
