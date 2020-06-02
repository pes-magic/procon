use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let a = (0..n).map(|_| it.next().unwrap().parse::<i64>().unwrap()).collect::<Vec<_>>();
    let m = 1_000_000_007;
    let mut inv = vec![1;n+1];
    for i in 2..n+1 {
		inv[i] = inv[m as usize % i] * (m - m / i as i64) % m;
    }
    let mut inv_sum = vec![1; n+1];
    for i in 1..n {
        inv_sum[i] = (inv_sum[i-1] + inv[i+1]) % m;
    }
    let mut res = 0;
    for i in 0..n {
        res += (inv_sum[i] + inv_sum[n-1-i] - 1) * a[i];
        res %= m;
    }
    for i in 1..n {
        res = ((i + 1) as i64 * res) % m;
    }
    println!("{}", res);
}
