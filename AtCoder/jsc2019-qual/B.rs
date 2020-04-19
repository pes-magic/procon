use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut iter = buf.split_whitespace();
    let n = iter.next().unwrap().parse::<usize>().unwrap();
    let k = iter.next().unwrap().parse::<i64>().unwrap();
    let a = (0..n).map(|_| iter.next().unwrap().parse::<i32>().unwrap()).collect::<Vec<_>>();
    let mut res : i64 = 0;
    let m = 1000000007;
    let mul =  (k * (k-1) / 2) % m;
    for i in 0..n {
        for j in 0..n {
            if a[j] < a[i] {
                res = (res + mul) % m;
                if i < j { res = (res + k) % m; }
            }
        }
    }
    println!("{}", res);
}
