fn main() {
    proconio::input! {
        n: usize,
        l: i32,
        vs: f64,
        ds: i32,
        mut car: [(i32, f64, i32); n]
    };
    car.push((0, vs, ds));
    car.push((l, 0.0, 0));
    let mut dp = vec![l as f64 + 100.0; n+2];
    dp[0] = 0.0;
    car.sort_by_key(|x| x.0);
    for i in 0..car.len()-1 {
        for j in i+1..car.len() {
            if car[i].0 + car[i].2 < car[j].0 { break }
            dp[j] = dp[j].min(dp[i] + (car[j].0 - car[i].0) as f64 / car[i].1);
        }
    }
    if dp[n+1] > l as f64 + 1.0 {
        println!("impossible");
    } else {
        println!("{:.10}", dp[n+1]);
    }
}
