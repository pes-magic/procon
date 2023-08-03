use proconio::input;

const MOD: i64 = 1000000007;

fn mod_pow(a: i64, p: i64) -> i64 {
    if p == 0 {
        return 1;
    }
    let mut res = mod_pow(a, p / 2);
    res = (res * res) % MOD;
    if p % 2 == 1 {
        res = (res * a) % MOD;
    }
    res
}

fn solve(h: &Vec<i64>, begin: usize, end: usize, cur_h: i64) -> (i64, i64) {
    let lowest = (begin..end).map(|i| h[i]).min().unwrap();
    let highest = (begin..end).map(|i| h[i]).max().unwrap().max(cur_h);
    if lowest == highest {
        return (
            mod_pow(2, lowest - cur_h),
            (mod_pow(2, (end - begin) as i64) + MOD - 2) % MOD,
        );
    }
    let mut all = 1;
    let mut one = 1;
    let mut last = None;
    let mut cnt = 0;
    for i in begin..=end {
        if i == end || h[i] == lowest {
            if i < end {
                cnt += 1;
            }
            if let Some(l) = last {
                let p = solve(h, l, i, lowest);
                all = (all * (2 * p.0 + p.1)) % MOD;
                one = (one * p.0) % MOD;
                last = None;
            }
        } else {
            if last == None {
                last = Some(i);
            }
        }
    }
    one = (2 * one) % MOD;
    all = (all * mod_pow(2, cnt)) % MOD;
    all = (all + MOD - one) % MOD;
    one = (one * mod_pow(2, lowest - cur_h - 1)) % MOD;
    (one, all)
}

fn main() {
    input! {
        n: usize,
        h: [i64;n]
    }
    let res = solve(&h, 0, n, 0);
    println!("{}", (res.0 + res.1) % MOD);
}
