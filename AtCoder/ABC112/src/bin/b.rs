use proconio::input;
fn main() {
    input! {
        n:usize, tl:usize,
        path: [(usize, usize);n]
    }
    let mut res: Option<usize> = None;
    for &(c, t) in &path {
        if t <= tl {
            if let Some(v) = res {
                res = Some(v.min(c));
            } else {
                res = Some(c);
            }
        }
    }
    if let Some(v) = res {
        println!("{}", v);
    } else {
        println!("TLE");
    }
}
