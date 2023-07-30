use proconio::input;

fn solve(a: &[i64]) -> Option<(i64, i64)> {
    let mut res = (2, 2);
    for v in a.iter().rev() {
        let new_res = ((res.0 + v - 1) / v * v, res.1 / v * v + v - 1);
        if new_res.0 > new_res.1 {
            return None;
        }
        res = new_res;
    }
    Some(res)
}

fn main() {
    input! {k:usize, a:[i64;k]}
    if let Some((l, r)) = solve(&a) {
        println!("{} {}", l, r);
    } else {
        println!("-1");
    }
}
