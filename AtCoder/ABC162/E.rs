use proconio::input;

fn mod_pow(a: u64, p: u64, m: u64) -> u64 {
    if p == 0 {
        1
    } else {
        let half = mod_pow(a, p/2, m);
        let res = half * half % m;
        if p % 2 == 0 { res } else  { res * a % m }
    }
}

fn main() {
    input! {
        n : u64,
        k : usize
    };
    let mut a = [0; 100001];
    let m : u64 = 1000000007;
    let mut res : u64 = 0;
    for i in (1..=k).rev() {
        a[i] = mod_pow((k/i) as u64, n, m);
        let mut j = 2 * i;
        while j <= k {
            a[i] = (a[i] + m - a[j]) % m;
            j += i;
        }
        res = (res + a[i] * i as u64) % m;
    }
    println!("{}", res);
}
