use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let s = buf.trim().as_bytes();
    let mut res = s.len();
    for i in 1..s.len() {
        if s[i] != s[i-1] {
            res = std::cmp::min(res, std::cmp::max(i, s.len()-i));
        }
    }
    println!("{}", res);
}
