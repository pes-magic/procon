use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let k = it.next().unwrap().parse::<i64>().unwrap();
    let a = (0..n).map(|_| it.next().unwrap().parse::<i64>().unwrap()).collect::<Vec<_>>();
    let mut sum = 0;
    let mut j = 0;
    let mut res = n * (n+1) / 2;
    for i in 0..n {
        while j < n && sum < k {
            sum += a[j];
            j += 1;
        }
        res -= j - i - 1;
        if sum < k { res -= 1; }
        sum -= a[i];
    }
    println!("{}", res);
}
