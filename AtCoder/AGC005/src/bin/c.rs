use proconio::input;

fn main() {
    input! {
        n: usize,
        d: [usize; n]
    }
    let mut cnt = vec![0; n];
    let min_value = *d.iter().min().unwrap();
    let max_value = *d.iter().max().unwrap();
    for &v in &d {
        cnt[v] += 1;
    }
    let mut ok = min_value == (max_value + 1) / 2;
    ok &= cnt[min_value] == 1 + max_value % 2;
    ok &= n == 2 || max_value >= 2;
    for i in min_value + 1..=max_value {
        ok &= cnt[i] >= 2;
    }
    println!("{}", if ok { "Possible" } else { "Impossible" });
}
