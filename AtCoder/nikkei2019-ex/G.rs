fn main() {
    proconio::input! {
        s : String
    }
    let mut cnt = [0; 26];
    for c in s.as_bytes() {
        cnt[(c-b'a') as usize] += 1;
    };
    let mut res = 0;
    for c in cnt.iter() {
        res += (c/2*2) as usize;
    }
    if res != s.len() { res += 1; }
    res = (s.len() - res) + res * res;
    println!("{}", res);
}
