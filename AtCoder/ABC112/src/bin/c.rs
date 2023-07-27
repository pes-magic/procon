use proconio::input;

fn main() {
    input! {n: usize, py: [(i32, i32, i32); n]}
    for x in 0..=100 {
        for y in 0..=100 {
            let mut lower = std::i32::MAX;
            let mut h = 0;
            let mut ok = true;
            for &(px, py, ph) in &py {
                let d = (x - px).abs() + (y - py).abs();
                if ph == 0 {
                    lower = lower.min(d);
                } else {
                    let h2 = d + ph;
                    if h == 0 {
                        h = h2;
                    } else if h != h2 {
                        ok = false;
                    }
                }
            }
            if ok && h <= lower {
                println!("{} {} {}", x, y, h);
            }
        }
    }
}
