use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let s = (0..n).map(|_| it.next().unwrap()).collect::<Vec<_>>();
    let mut res = 0;
    let mut cnt_a = 0;
    let mut cnt_b = 0;
    let mut check_ab = false;
    for &c in &s {
        res += c.matches("AB").count();
        let start_b = c.starts_with("B");
        let end_a = c.ends_with("A");
        if start_b && end_a {
            if check_ab {
                res += 1;
            } else {
                check_ab = true;
            }
        } else if start_b {
            cnt_b += 1;
        } else if end_a {
            cnt_a += 1;
        }
    }
    if check_ab {
        if cnt_a > 0 {
            res += 1;
            cnt_a -= 1;
        }
        if cnt_b > 0 {
            res += 1;
            cnt_b -= 1;
        }
    }
    res += std::cmp::min(cnt_a, cnt_b);
    println!("{}", res);
}
