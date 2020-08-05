fn main() {
    proconio::input! {
        n: usize,
        k: i64,
        a: [i64; n]
    };
    let mut l = 0;
    let mut r = 1000000000;
    while r - l > 1 {
        let mid = (l + r) / 2;
        let cut = a.iter().fold(0, |s, x| s + (x-1)/mid);
        if cut <= k {
            r = mid;
        } else {
            l = mid;
        }
    }
    println!("{}", r);
}
