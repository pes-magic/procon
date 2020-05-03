use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let case_num = it.next().unwrap().parse::<usize>().unwrap();
    for t in 0..case_num {
        let mut x = it.next().unwrap().parse::<i32>().unwrap();
        let mut y = it.next().unwrap().parse::<i32>().unwrap();
        let s = it.next().unwrap().as_bytes();
        let mut res = -1;
        for i in 0..s.len() {
            match s[i] {
                b'S' => { y -= 1; }
                b'N' => { y += 1; }
                b'W' => { x -= 1; }
                b'E' => { x += 1; }
                _ => {}
            };
            if x.abs() + y.abs() <= i as i32 + 1 {
                res = i as i32 + 1;
                break;
            }
        }
        println!("Case #{}: {}", t+1, if res > 0 { res.to_string() } else { "IMPOSSIBLE".to_string() });
    }
}
