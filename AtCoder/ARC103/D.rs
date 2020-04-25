use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let p : Vec<(i64, i64)> = (0..n).map(|_| (it.next().unwrap().parse().unwrap(), it.next().unwrap().parse().unwrap())).collect();
    let mut b = vec![0; 31];
    for i in 0..31 { b[i] = 1 << (30 - i as i64) }
    let mut cnt_odd = 0;
    for &pt in &p {
        cnt_odd += (pt.0.abs() + pt.1.abs()) % 2;
    }
    if cnt_odd == 0 {
        b.push(1)
    } else if cnt_odd < n as i64 {
        println!("-1");
        return;
    }
    println!("{}", b.len());
    print!("{}", b[0]);
    for i in 1..b.len() { print!(" {}", b[i]); }
    println!("");
    for &pt in &p {
        let mut x = pt.0;
        let mut y = pt.1;
        let mut res = vec!();
        let dir = [b'D', b'L', b'U', b'R'];
        for &d in &b {
            let dx = vec![0, -d, 0, d];
            let dy = vec![-d, 0, d, 0];
            let mut max_dist = 1 << 40;
            let mut min_idx = 0;
            for i in 0..4 {
                let cur_dist = (x - dx[i]).abs() + (y - dy[i]).abs();
                if cur_dist < max_dist {
                    max_dist = cur_dist;
                    min_idx = i;
                }
            }
            res.push(dir[min_idx]);
            x -= dx[min_idx];
            y -= dy[min_idx];
        }
        println!("{}", String::from_utf8(res).unwrap());
    }
}