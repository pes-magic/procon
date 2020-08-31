fn main() {
    proconio::input! {
        s: String,
        t: String
    };
    let a = s.as_bytes();
    let b = t.as_bytes();
    let mut res = b.len();
    for i in 0..=(a.len()-b.len()) {
        let mut cnt = 0;
        for j in 0..b.len() {
            if a[i+j] != b[j] { cnt += 1 }
        }
        res = res.min(cnt);
    }
    println!("{}", res);
}
