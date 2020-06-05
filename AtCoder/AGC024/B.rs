use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let a = (0..n).map(|_| it.next().unwrap().parse::<usize>().unwrap()).collect::<Vec<_>>();
    let mut b = vec![0; n];
    for i in 0..n {
        b[a[i]-1] = i;
    }
    let mut res = 0;
    let mut cnt = 0;
    let mut pos = 0;
    for &t in &b {
        cnt = if t >= pos { cnt + 1} else { 1 };
        res = std::cmp::max(res, cnt);
        pos = t;
    }
    println!("{}", n - res);
}
