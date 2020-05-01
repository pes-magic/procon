use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let n = buf.trim().parse::<u64>().unwrap();
    let mut res = n as usize;
    for i in 1..n {
        if i*i > n { break; }
        if n%i != 0 { continue; }
        res = std::cmp::min(res, std::cmp::max(i.to_string().len(), (n/i).to_string().len()));
    }
    println!("{}", res);
}
