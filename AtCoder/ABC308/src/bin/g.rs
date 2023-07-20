use proconio::input;
use std::collections::{BTreeMap, BTreeSet};

fn main() {
    input! { q:usize }
    let mut res = BTreeSet::new();
    let mut res_cnt = BTreeMap::new();
    let mut values = BTreeSet::new();
    let mut value_cnt = BTreeMap::new();
    for _ in 0..q {
        input! { c:usize }
        match c {
            1 => {
                input! { x: u32 }
                let left = values.range(x..).next();
                let right = values.range(..x).last();
                if let Some(v) = left {
                    res.insert(v ^ x);
                    *res_cnt.entry(v ^ x).or_insert(0) += 1;
                    if let Some(w) = right {
                        let val = v ^ w;
                        *res_cnt.entry(val).or_insert(0) -= 1;
                        if res_cnt[&val] == 0 {
                            res.remove(&val);
                            res_cnt.remove(&val);
                        }
                    }
                }
                if let Some(v) = right {
                    res.insert(v ^ x);
                    *res_cnt.entry(v ^ x).or_insert(0) += 1;
                }
                values.insert(x);
                *value_cnt.entry(x).or_insert(0) += 1;
            }
            2 => {
                input! { x: u32 }
                *value_cnt.entry(x).or_insert(0) -= 1;
                if value_cnt[&x] == 0 {
                    values.remove(&x);
                    value_cnt.remove(&x);
                }
                let left = values.range(x..).next();
                let right = values.range(..x).last();
                if let Some(v) = left {
                    let val = v ^ x;
                    *res_cnt.entry(val).or_insert(0) -= 1;
                    if res_cnt[&val] == 0 {
                        res.remove(&val);
                        res_cnt.remove(&val);
                    }
                    if let Some(w) = right {
                        res.insert(v ^ w);
                        *res_cnt.entry(v ^ w).or_insert(0) += 1;
                    }
                }
                if let Some(v) = right {
                    let val = v ^ x;
                    *res_cnt.entry(val).or_insert(0) -= 1;
                    if res_cnt[&val] == 0 {
                        res.remove(&val);
                        res_cnt.remove(&val);
                    }
                }
            }
            _ => {
                println!("{}", res.iter().next().unwrap());
            }
        }
    }
}
