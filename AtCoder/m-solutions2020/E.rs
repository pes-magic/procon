fn main() {
    proconio::input! {
        n: usize,
        city: [(i64, i64, i64); n]
    };
    let mut dist_v = vec![vec![0; n]; 1<<n];
    let mut dist_h = vec![vec![0; n]; 1<<n];
    for i in 0..1<<n {
        for j in 0..n {
            dist_v[i][j] = city[j].0.abs();
            dist_h[i][j] = city[j].1.abs();
            for k in 0..n {
                if i&(1<<k) == 0 { continue }
                dist_v[i][j] = dist_v[i][j].min((city[k].0-city[j].0).abs());
                dist_h[i][j] = dist_h[i][j].min((city[k].1-city[j].1).abs());
            }
            dist_v[i][j] *= city[j].2;
            dist_h[i][j] *= city[j].2;
        }
    }
    let mut res = vec![1000000000000000000; n+1];
    for i in 0..1<<n {
        let idx = (i as u64).count_ones() as usize;
        let mut j = i;
        loop {
            let mut cur = 0;
            for k in 0..n {
                cur += dist_v[j][k].min(dist_h[i^j][k]);
            }
            res[idx] = res[idx].min(cur);
            if j == 0 { break; }
            j = i&(j-1);
        }
    }
    for &v in &res { println!("{}", v) }
}
