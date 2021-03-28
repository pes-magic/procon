use std::io::Read;

fn solve(n: usize, c: usize) -> Option<Vec<usize>> {
    let mut a : Vec<usize> = (0..n).map(|i| i+1).collect();
    if c < n-1 { return None }
    let mut rest = c-(n-1);
    for i in (0..n-1).rev() {
        let mov = rest.min(n-1-i);
        let pos = i+mov;
        for j in i..n {
            if j >= pos+i-j { break }
            let tmp = a[pos+i-j];
            a[pos+i-j] = a[j];
            a[j] = tmp;
        }
        rest -= mov;
    }
    if rest == 0 { Some(a) } else { None }
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let case_num = it.next().unwrap().parse::<usize>().unwrap();
    for t in 0..case_num {
        print!("Case #{}:", t+1);
        let n = it.next().unwrap().parse::<usize>().unwrap();
        let c = it.next().unwrap().parse::<usize>().unwrap();
        if let Some(a) = solve(n, c) {
            for &v in &a {
                print!(" {}", v);
            }
        } else {
            print!(" IMPOSSIBLE");
        }
        println!("");
    }
}
