use std::io::Read;
use std::collections::HashSet;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let case_num = it.next().unwrap().parse::<usize>().unwrap();
    for t in 0..case_num {
        let _b = it.next().unwrap();
        let mut s = HashSet::new();
        let mut v = Vec::new();
        for _ in 0..10000 {
            let _q = it.next().unwrap();
            let p = it.next().unwrap().as_bytes();
            for &c in p { s.insert(c); }
            v.push(p[0]);
        }
        let mut cnt = Vec::new();
        for c in s {
            cnt.push((c, v.iter().filter(|&&x| x == c).count()));
        }
        cnt.sort_by(|a, b| b.1.cmp(&a.1));
        let mut res = vec![0; 10];
        for i in 0..10 { res[(i+1)%10] = cnt[i].0; }
        println!("Case #{}: {}", t+1, String::from_utf8(res).unwrap());
    }
}
