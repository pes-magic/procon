fn main() {
    proconio::input! {
        n: usize,
        p: [(i32, i32); n]
    }
    let mut res = 0;
    for i in 0..n-1 {
        res += (p[i+1].0 - p[i].0).abs();
        res += (p[i+1].1 - p[i].1).abs();
    }
    println!("{}", res);
}
