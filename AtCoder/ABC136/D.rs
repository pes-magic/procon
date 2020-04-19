use std::io::Read;

fn main() {
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).ok();
    let c = s.trim_right().as_bytes();
    let n = c.len();
    let mut res = vec!(0; n);
    let mut cnt = 0;
    for i in 0..n {
        if c[i] == 'L' as u8 {
            res[i] += cnt / 2;
            res[i-1] += (cnt + 1) / 2;
            cnt = 0;
        } else {
            cnt += 1;
        }
    }
    for i in (0..n).rev() {
        if c[i] == 'R' as u8 {
            res[i] += cnt / 2;
            res[i+1] += (cnt + 1) / 2;
            cnt = 0;
        } else {
            cnt += 1;
        }
    }
    print!("{}", res[0]);
    for i in 1..n { print!(" {}", res[i]); }
    println!("");
}
