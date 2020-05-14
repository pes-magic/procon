use std::io::Read;

fn check(s : &[u8], t : &[u8]) -> bool {
    let n = s.len();
    let mut m = [26; 26];
    for i in 0..n {
        let a = (s[i] - b'a') as usize;
        let b = t[i] - b'a';
        if m[a] == 26 {
            m[a] = b
        } else if m[a] != b {
            return false;
        }
    }
    true
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let s = it.next().unwrap().as_bytes();
    let t = it.next().unwrap().as_bytes();
    println!("{}", if check(s, t) && check(t, s) { "Yes" } else { "No" });
}
