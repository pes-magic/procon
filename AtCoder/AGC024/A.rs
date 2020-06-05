use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let a = it.next().unwrap().parse::<i64>().unwrap();
    let b = it.next().unwrap().parse::<i64>().unwrap();
    let c = it.next().unwrap().parse::<i64>().unwrap();
    let k = it.next().unwrap().parse::<i64>().unwrap();
    println!("{}", if k%2 == 0 { a-b } else { b-a });
}
