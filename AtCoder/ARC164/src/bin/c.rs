use proconio::input;

fn main() {
    input! {
        n:usize,
        c: [(i64,i64);n]
    }
    let mut res = 0;
    let mut sub = std::i64::MAX;
    let mut cnt = 0;
    for s in c {
        res += s.0.max(s.1);
        sub = sub.min((s.0 - s.1).abs());
        if s.0 > s.1 {
            cnt = 1 - cnt;
        }
    }
    if cnt == 1 {
        res -= sub;
    }
    println!("{}", res);
}
