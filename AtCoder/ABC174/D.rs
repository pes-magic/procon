fn main() {
    proconio::input! {
        _n: usize,
        s: String
    };
    let c = s.as_bytes();
    let r = c.iter().filter(|&&x| x == b'R' ).count();
    let mut res = 0;
    for i in 0..r {
        if c[i] == b'W' { res += 1 }
    }
    println!("{}", res);
}
