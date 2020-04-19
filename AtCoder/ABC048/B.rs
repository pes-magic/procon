use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let a = it.next().unwrap().parse::<i64>().unwrap();
    let b = it.next().unwrap().parse::<i64>().unwrap();
    let x = it.next().unwrap().parse::<i64>().unwrap();
    let f = |s : i64, t : i64| { if s >= 0 { s / t + 1 } else { 0 } };
    println!("{}", f(b, x) - f(a-1, x));
}
