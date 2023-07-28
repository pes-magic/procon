use proconio::input;

fn main() {
    input! {
        n: usize, l: usize,
        k: usize,
        pos: [usize; n]
    }
    let mut low = 0;
    let mut high = l;
    while high - low >= 2 {
        let mid = (high + low) / 2;
        let mut last = 0;
        let mut cut = 0;
        let mut ok = false;
        for &p in &pos {
            if p - last >= mid {
                cut += 1;
                last = p;
                if cut == k {
                    ok = (l - last) >= mid;
                    break;
                }
            }
        }
        if ok {
            low = mid;
        } else {
            high = mid;
        }
    }
    println!("{}", low);
}
