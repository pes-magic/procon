use proconio::input;
use std::collections::VecDeque;

fn main() {
    input! {
        h :usize,
        w :usize,
        s :[String;h]
    }
    let mut visit = vec![vec![vec![false; 5]; w]; h];
    let mut qu = VecDeque::new();
    if s[0].chars().nth(0) == Some('s') {
        qu.push_back((0, 0, 0));
        visit[0][0][0] = true;
    }
    let snuke = "snuke".to_string();
    while let Some((x, y, z)) = qu.pop_front() {
        for &(dx, dy) in &[(0, !0), (!0, 0), (0, 1), (1, 0)] {
            let nx = x + dx;
            let ny = y + dy;
            if nx >= h || ny >= w {
                continue;
            }
            let nz = (z + 1) % 5;
            if visit[nx][ny][nz] {
                continue;
            }
            if s[nx].chars().nth(ny) == snuke.chars().nth(nz) {
                qu.push_back((nx, ny, nz));
                visit[nx][ny][nz] = true;
            }
        }
    }
    let ok = visit[h - 1][w - 1].iter().any(|b| *b);
    println!("{}", if ok { "Yes" } else { "No" });
}
