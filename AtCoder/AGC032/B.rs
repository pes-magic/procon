use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let ng = if n%2 == 0 { n+1 } else { n };
    let mut res = Vec::new();
    for i in 1..n {
        for j in i+1..n+1 {
            if i+j == ng { continue }
            res.push((i, j));
        }
    }
    println!("{}", res.len());
    for &p in &res {
        println!("{} {}", p.0, p.1);
    }
}
