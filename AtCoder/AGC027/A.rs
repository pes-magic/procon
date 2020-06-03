use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut x = it.next().unwrap().parse::<i32>().unwrap();
    let mut a = (0..n).map(|_| it.next().unwrap().parse::<i32>().unwrap()).collect::<Vec<_>>();
    a.sort();
    let mut res = 0;
    for &t in &a {
        if t <= x {
            x -= t;
            res += 1;
        }
    }
    if res == n && x != 0 { res -= 1; }
    println!("{}", res);
}
