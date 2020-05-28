use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<i64>().unwrap();
    let x = it.next().unwrap().parse::<i64>().unwrap();
    let mut t = Vec::new();
    let mut aoki = 0;
    for _ in 0..n {
        let b = it.next().unwrap().parse::<i64>().unwrap();
        let l = it.next().unwrap().parse::<i64>().unwrap();
        let u = it.next().unwrap().parse::<i64>().unwrap();
        let mx = b * l + (x - b) * u;
        aoki += b * l;
        t.push((b, l, u, mx));
    }
    t.sort_by_key(|a| -a.3);
    let mut low = -1;
    let mut high = n * x;
    while high - low > 1 {
        let mid = (low + high) / 2;
        let thr = (mid / x) as usize;
        let y = mid % x;
        let mut sum = 0;
        for i in 0..thr { sum += t[i].3 }
        let mut best = 0;
        for i in 0..n as usize {
            let mut cur = sum;
            if i < thr {
                cur += t[thr].3 - t[i].3;
            }
            cur += std::cmp::min(t[i].0, y) * t[i].1 + std::cmp::max(0, y - t[i].0) * t[i].2;
            best = std::cmp::max(best, cur);
        }
        if best >= aoki {
            high = mid;
        } else {
            low = mid;
        }
    }
    println!("{}", high);
}

