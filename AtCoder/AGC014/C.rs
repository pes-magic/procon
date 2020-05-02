use std::io::Read;
use std::collections::VecDeque;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let h = it.next().unwrap().parse::<usize>().unwrap();
    let w = it.next().unwrap().parse::<usize>().unwrap();
    let k = it.next().unwrap().parse::<usize>().unwrap();
    let s = (0..h).map(|_| it.next().unwrap().as_bytes()).collect::<Vec<_>>();
    let mut res = h*w;
    for i in 0..h {
        for j in 0..w {
            if s[i][j] != b'S' { continue; }
            let mut dist = vec![vec![h*w; w]; h];
            let mut qu = VecDeque::new();
            dist[i][j] = 0;
            qu.push_back((i, j));
            let dx = [-1, 0, 1, 0];
            let dy = [0, -1, 0, 1];
            while !qu.is_empty() {
                let (cx, cy) = qu.pop_front().unwrap();
                res = std::cmp::min(res, ([cx, h-cx-1, cy, w-cy-1].iter().min().unwrap() + k - 1)/k + 1);
                if cx == 0 || cx == h-1 || cy == 0 || cy == w-1 { continue; }
                if dist[cx][cy] == k { continue; }
                for dir in 0..4 {
                    let nx = (cx as i32 + dx[dir]) as usize;
                    let ny = (cy as i32 + dy[dir]) as usize;
                    if s[nx][ny] == b'#' { continue; }
                    if dist[cx][cy] + 1 >= dist[nx][ny] { continue; }
                    dist[nx][ny] = dist[cx][cy] + 1;
                    qu.push_back((nx, ny));
                }
            }
        }
    }
    println!("{}", res);
}
