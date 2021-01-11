use std::collections::HashMap;

fn search(x: i64, y: i64, mem: &mut HashMap<i64, i64>) -> i64 {
    if y <= x {
        return x - y
    } else if let Some(v) = mem.get(&y) {
        return *v
    }
    let mut res = y - x;
    if y%2 == 0 {
        res = res.min(search(x, y/2, mem)+1);
    } else {
        res = res.min(search(x, y+1, mem)+1);
        res = res.min(search(x, y-1, mem)+1);
    }
    mem.insert(y, res);
    res
}

fn main() {
    proconio::input! {
        x: i64,
        y: i64
    };
    let mut mem = HashMap::<i64, i64>::new();
    println!("{}", search(x, y, &mut mem));
}
