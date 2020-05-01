use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let _n = it.next().unwrap().parse::<usize>().unwrap();
    let s = it.next().unwrap().as_bytes();
    let mut res = 0;
    for i in 0..1000 {
        let mut m : u32 = i;
        let mut cnt = 0;
        for &c in s {
            if c == b'0' + (m%10) as u8 {
                cnt += 1;
                m /= 10;
            }
        }
        if cnt >= 3 { res += 1; }
    }
    println!("{}", res);
}
