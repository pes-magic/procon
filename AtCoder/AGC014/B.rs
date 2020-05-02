use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let m = it.next().unwrap().parse::<usize>().unwrap();
    let mut cnt = vec![0; n];
    for _ in 0..2*m {
        cnt[it.next().unwrap().parse::<usize>().unwrap() - 1] += 1;
    }
    println!("{}", if cnt.iter().all(|x| x%2 == 0) { "YES" } else { "NO" });
}
