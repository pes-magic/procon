use proconio::input;
use proconio::marker::Chars;
use std::collections::VecDeque;

fn main() {
    input! {n:usize, m:usize, s:[Chars;n]}
    let mut stop = vec![vec![false; m]; n];
    let mut visit = vec![vec![0; m]; n];
    let mut qu = VecDeque::new();
    qu.push_back((1, 1));
    stop[1][1] = true;
    visit[1][1] = 1;
    while let Some((x, y)) = qu.pop_front() {
        for &(dx, dy) in &[(0, !0), (!0, 0), (0, 1), (1, 0)] {
            let mut nx = x;
            let mut ny = y;
            while s[nx + dx][ny + dy] == '.' {
                nx += dx;
                ny += dy;
                visit[nx][ny] = 1;
            }
            if !stop[nx][ny] {
                stop[nx][ny] = true;
                qu.push_back((nx, ny));
            }
        }
    }
    println!(
        "{}",
        visit.iter().map(|c| c.iter().sum::<i32>()).sum::<i32>()
    );
}
