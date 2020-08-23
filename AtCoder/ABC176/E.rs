fn main() {
    proconio::input! {
        h: usize,
        w: usize,
        m: usize,
        b: [(usize, usize); m]
    };
    let mut cnt_h = vec![0; h+1];
    let mut cnt_w = vec![0; w+1];
    for &p in &b {
        cnt_h[p.0] += 1;
        cnt_w[p.1] += 1;
    }
    let max_h = cnt_h.iter().max().unwrap();
    let max_w = cnt_w.iter().max().unwrap();
    let mut overlap = cnt_h.iter().filter(|&x| x == max_h).count() * cnt_w.iter().filter(|&x| x == max_w).count();
    for &p in &b {
        if cnt_h[p.0] == *max_h && cnt_w[p.1] == *max_w { overlap -= 1; }
    }
    println!("{}", max_h + max_w - if overlap == 0 { 1 } else { 0 });
}
