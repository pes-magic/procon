use std::io::Read;
use std::collections::HashMap;

const MOD: u64 = 998244353;

fn solve(s: u128, n: usize, mem: &mut HashMap<(u128, usize), u64>) -> u64 {
    if n == 0 { return 1 }
    if n == 1 { return (s%2 + 1) as u64 }
    if let Some(&r) = mem.get(&(s, n)) { return r }
    let mut res = (s%2 + 1) as u64 * solve(s/2, n-1, mem) % MOD;
    for l in 1..n {
        if 2*l > n { break }
        let mut ns = s & (s >> l);
        for r in 2..=n/l {
            if l*r > n { break; }
            res = (res + solve(ns, l, mem) * solve(s >> r*l, n-r*l, mem)) % MOD;
            ns &= s >> r*l;
        }
    }
    mem.insert((s, n), res);
    res
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let s = buf.trim().as_bytes();
    let n = s.len();
    let mut v : u128 = 0;
    for i in 0..n {
        if s[i] == b'1' { v |= 1 << i }
    }
    let mut mem = HashMap::new();
    let res = solve(v, n, &mut mem);
    println!("{}", res);
}
