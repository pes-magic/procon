use proconio::input;

fn check(arr : &Vec<(i32, i32)>) -> i32 {
    let mut res = 0;
    for &a in arr {
        res -= a.1;
        if res < 0 { return -1; }
        res += a.0;
    }
    return res;
}

fn main() {
    input! {
        n : usize,
        s : [String; n]
    };
    let mut up = Vec::new();
    let mut down = Vec::new();
    for c in s {
        let mut p = (0, 0);
        for &v in c.as_bytes() {
            if v == b'(' { p.0 += 1 }
            else {
                if p.0 > 0 { p.0 -= 1 }
                else { p.1 += 1 }
            }
        }
        if p.0 >= p.1 {
            up.push(p)
        } else {
            down.push((p.1, p.0))
        }
    }
    up.sort_by_key(|x| x.1);
    down.sort_by_key(|x| x.1);
    let a = check(&up);
    let b = check(&down);
    println!("{}", if a >= 0 && b >= 0 && a == b { "Yes" } else { "No" });
}
