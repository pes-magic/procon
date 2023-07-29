use itertools::Itertools;
use proconio::input;

fn main() {
    input! {n:usize}
    if n % 2 == 1 {
        return;
    }
    let pos: Vec<usize> = (0..n).collect();
    let pattern = pos.iter().copied().combinations(n / 2);
    for p in pattern {
        let mut sum = 0;
        let mut ok = true;
        let mut idx = 0;
        for i in 0..n {
            if idx != n / 2 && i == p[idx] {
                idx += 1;
                sum += 1;
            } else {
                sum -= 1;
            }
            ok &= sum >= 0;
        }
        if ok {
            idx = 0;
            for i in 0..n {
                if idx != n / 2 && i == p[idx] {
                    print!("(");
                    idx += 1;
                } else {
                    print!(")");
                }
            }
            println!("");
        }
    }
}
