use std::collections::HashMap;

fn main() {
    proconio::input! {
        h: i64,
        w: i64,
        n: usize,
        black: [(i64, i64); n]
    }
    let mut cnt = HashMap::new();
    for &p in &black {
        for dx in -1..=1 {
            if p.0+dx <= 1 || h <= p.0+dx { continue }
            for dy in -1..=1 {
                if p.1+dy <= 1 || w <= p.1+dy { continue }
                let pt = (p.0+dx, p.1+dy);
                if let Some(c) = cnt.get(&pt) {
                    cnt.insert(pt, c+1);
                } else {
                    cnt.insert(pt, 1);
                }
            }
        }
    }
    let mut res = vec![0; 10];
    res[0] = (h-2)*(w-2);
    for (_, &value) in &cnt {
        res[0] -= 1;
        res[value as usize] += 1;
    }
    for &t in &res { println!("{}", t) }
}
