use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut iter = buf.split_whitespace();
    let t = iter.next().unwrap().parse::<usize>().unwrap();
    for case_id in 1..=t {
        let n = iter.next().unwrap().parse::<usize>().unwrap();
        let i = iter.next().unwrap().as_bytes();
        let o = iter.next().unwrap().as_bytes();
        println!("Case #{}:", case_id);
        for j in 0..n {
            for k in 0..n {
                let mut valid = true;
                if j < k {
                    for l in j..k {
                        if o[l] == b'N' || i[l+1] == b'N' { valid = false }
                    }
                } else if j > k {
                    for l in (k+1..=j).rev() {
                        if o[l] == b'N' || i[l-1] == b'N' { valid = false }
                    }
                }
                print!("{}", if valid { "Y" } else { "N" })
            }
            println!("");
        }
    }
}
