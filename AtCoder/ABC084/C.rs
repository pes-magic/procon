use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap() - 1;
    let mut t = Vec::new();
    for _ in 0..n {
        let c = it.next().unwrap().parse::<i64>().unwrap();
        let s = it.next().unwrap().parse::<i64>().unwrap();
        let f = it.next().unwrap().parse::<i64>().unwrap();
        t.push((c, s, f));
    }
    for i in 0..n {
        let mut cur = 0;
        for j in i..n {
            cur = std::cmp::max(t[j].1, cur + t[j].2 - 1) / t[j].2 * t[j].2 + t[j].0;
        }
        println!("{}", cur);
    }
    println!("0");
}
