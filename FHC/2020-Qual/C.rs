use std::io::Read;
use std::collections::BTreeMap;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let t = it.next().unwrap().parse::<usize>().unwrap();
    for case_id in 1..=t {
        let n = it.next().unwrap().parse::<usize>().unwrap();
        let mut tree = Vec::new();
        for _ in 0..n {
            let p = it.next().unwrap().parse::<i64>().unwrap();
            let h = it.next().unwrap().parse::<i64>().unwrap();
            tree.push((p, h));
        }
        tree.push((1_000_000_000, 1));
        tree.sort();
        let mut dp : BTreeMap<i64, i64> = BTreeMap::new();
        let mut hs = Vec::new();
        let mut prev = tree[0].0;
        for &l in &tree {
            if prev == l.0 {
                hs.push(l.1);
            } else {
                let mut best_l1 = 0;
                let mut best_r1 = 0;
                let mut best_r2 = 0;
                if let Some(v) = dp.get(&prev) { best_r1 = *v; }
                for &h in &hs {
                    let mut pre = 0;
                    if let Some(v) = dp.get(&(prev-h)) { pre = *v; }
                    if best_r1 < pre + h {
                        best_r2 = best_r1;
                        best_l1 = h;
                        best_r1 = pre + h;
                    } else if best_r2 < pre + h {
                        best_r2 = pre + h;
                    }
                }
                if best_r1 > 0 {
                    if dp.get(&prev) == None {
                        dp.insert(prev, best_r1);
                    } else {
                        dp.insert(prev, dp[&prev].max(best_r1));
                    }
                }
                for &h in &hs {
                    if dp.get(&(prev+h)) == None {
                        dp.insert(prev+h, if best_l1 != h { best_r1 } else { best_r2 } + h);
                    } else {
                        dp.insert(prev+h, dp[&(prev+h)].max(if best_l1 != h { best_r1 } else { best_r2 } + h));
                    }
                }
                hs.clear();
                prev = l.0;
                hs.push(l.1);
            }
        }
        println!("Case #{}: {}", case_id, dp.values().max().unwrap());
    }
}
