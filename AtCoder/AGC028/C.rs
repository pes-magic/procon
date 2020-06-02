use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut a = Vec::new();
    for i in 0..n {
        for j in 0..2 {
            let v = it.next().unwrap().parse::<i64>().unwrap();
            a.push((v, i, j));
        }
    }
    a.sort();
    let mut res = 0;
    let mut ok = false;
    let mut cnt_in = 0;
    let mut used = vec![0; n];
    for i in 0..n {
        res += a[i].0;
        used[a[i].1] += 1;
        if used[a[i].1] == 2 { ok = true; }
        if a[i].2 == 0 { cnt_in += 1; }
    }
    if cnt_in != n && cnt_in != 0 && !ok {
        let mut dif = 1_000_000_000_000_000_000;
        for i in 0..n {
            dif = std::cmp::min(dif, a[if a[i].1 != a[n].1 || cnt_in == 1 || cnt_in == n-1 { n } else { n+1 }].0 - a[i].0);
        }
        res += dif;
    }
    println!("{}", res);
}
