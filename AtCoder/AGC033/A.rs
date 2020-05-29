use std::io::Read;
use std::collections::VecDeque;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let h = it.next().unwrap().parse::<usize>().unwrap();
    let w = it.next().unwrap().parse::<usize>().unwrap();
    let s = (0..h).map(|_| it.next().unwrap().as_bytes()).collect::<Vec<_>>();
    let mut qu = VecDeque::new();
    let mut step = vec![vec![h*w; w]; h];
    let mut res = 0;
    for i in 0..h {
        for j in 0..w {
            if s[i][j] == b'#' {
                step[i][j] = 0;
                qu.push_back((i, j));
            }
        }
    }
    while !qu.is_empty() {
        let (x, y) = qu.pop_front().unwrap();
        res = step[x][y];
        for &(dx, dy) in [(1, 0), (0, 1), (!0, 0), (0, !0)].iter() {
            let nx = x.wrapping_add(dx);
            let ny = y.wrapping_add(dy);
            if nx >= h || ny >= w { continue }
            if step[nx][ny] <= step[x][y] + 1 { continue }
            step[nx][ny] = step[x][y] + 1;
            qu.push_back((nx, ny));
        }
    }
    println!("{}", res);
}
