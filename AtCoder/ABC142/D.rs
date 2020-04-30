use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let a = it.next().unwrap().parse::<u64>().unwrap();
    let b = it.next().unwrap().parse::<u64>().unwrap();
    let mut div : Vec<u64> = Vec::new();
    for i in 2..a {
        if i * i > a { break; }
        if a % i == 0 {
            if b % i == 0 { div.push(i) }
            if b % (a/i) == 0 { div.push(a/i) }
        }
    }
    if a > 1 && b % a == 0 { div.push(a); }
    div.sort();
    let mut res : Vec<u64> = Vec::new();
    for d in div {
        if res.iter().all(|x| d % x != 0) { res.push(d); }
    }
    println!("{}", res.len() + 1);
}
