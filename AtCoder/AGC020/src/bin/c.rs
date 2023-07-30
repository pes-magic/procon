use bitset_fixed::BitSet;
use proconio::input;

fn main() {
    input! {n:usize, a:[usize;n]}
    let s = a.iter().sum::<usize>();
    let mut dp = BitSet::new(s + 1);
    dp.set(0, true);
    for &v in &a {
        dp.shl_or(v);
    }
    for i in (s + 1) / 2..=s {
        if dp[i] {
            println!("{}", i);
            break;
        }
    }
}
