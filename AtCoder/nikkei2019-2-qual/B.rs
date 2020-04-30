use std::io::Read;

const MOD : u64 = 998_244_353;

fn pow(a: u64, p: u64) -> u64 {
    if p == 0 { 1 }
    else {
        let mut res = pow(a, p/2);
        res = (res * res) % MOD;
        if p%2 == 1 { res = (res * a) % MOD; }
        res
    }
}

fn solve(cnt: Vec<u64>, num: u64) -> u64 {
    if cnt[0] != 1 { return 0; }
    if num == 1 { return 1; }
    let mut res = 1;
    let mut sum = 1;
    for i in 1..cnt.len() {
        if cnt[i] == 0 { return 0; }
        res = res * pow(cnt[i-1], cnt[i]) % MOD;
        sum += cnt[i];
        if sum == num { break; }
    }
    res
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut cnt = vec![0; n];
    let mut valid = true;
    for i in 0..n {
        let idx = it.next().unwrap().parse::<usize>().unwrap();
        if (i == 0)^(idx == 0) { valid = false; }
        cnt[idx] += 1;
    }
    println!("{}", if valid { solve(cnt, n as u64) } else { 0 });
}
