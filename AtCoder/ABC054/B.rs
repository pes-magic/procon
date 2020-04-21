use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let m = it.next().unwrap().parse::<usize>().unwrap();
    let a = (0..n).map(|_| it.next().unwrap()).collect::<Vec<_>>();
    let b = (0..m).map(|_| it.next().unwrap()).collect::<Vec<_>>();
    let mut valid = false;
    for i in 0..n-m+1 {
        for j in 0..n-m+1 {
            let mut eq = true;
            for k in 0..m {
                if &a[i+k][j..j+m] != b[k] { eq = false; }
            }
            if eq { valid = true; }
        }
    }
    println!("{}", if valid { "Yes" } else { "No" });
}
