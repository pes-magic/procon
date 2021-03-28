use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let case_num = it.next().unwrap().parse::<usize>().unwrap();
    for t in 0..case_num {
        let n = it.next().unwrap().parse::<usize>().unwrap();
        let mut a : Vec<usize> = (0..n).map(|_| it.next().unwrap().parse::<usize>().unwrap()).collect();
        let mut res = 0;
        for i in 0..n-1 {
            let mut pos = i;
            for j in i..n {
                if a[j] == i+1 { pos = j; }
            }
            res += pos - i + 1;
            for j in i..n {
                if j >= pos+i-j { break }
                let tmp = a[pos+i-j];
                a[pos+i-j] = a[j];
                a[j] = tmp;
            }
        }
        println!("Case #{}: {}", t+1, res);
    }
}
