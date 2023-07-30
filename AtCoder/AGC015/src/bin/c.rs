use proconio::input;
use proconio::marker::Chars;
use proconio::marker::Usize1;

fn make_sum(a: &mut Vec<Vec<i32>>) {
    for i in 0..a.len() {
        for j in 1..a[i].len() {
            a[i][j] += a[i][j - 1];
        }
    }
    for i in 1..a.len() {
        for j in 0..a[i].len() {
            a[i][j] += a[i - 1][j];
        }
    }
}

fn get_sum(a: &Vec<Vec<i32>>, x1: usize, y1: usize, x2: usize, y2: usize) -> i32 {
    a[x2][y2] - a[x2][y1] - a[x1][y2] + a[x1][y1]
}

fn main() {
    input! {
        n:usize, m:usize, q:usize,
        s: [Chars;n],
        queries: [(Usize1, Usize1, usize, usize); q]
    }
    let mut blue = vec![vec![0; m + 1]; n + 1];
    let mut right = vec![vec![0; m + 1]; n + 1];
    let mut up = vec![vec![0; m + 1]; n + 1];
    for i in 0..n {
        for j in 0..m {
            if s[i][j] == '1' {
                blue[i + 1][j + 1] = 1;
            }
        }
    }
    for i in 0..=n {
        for j in 0..=m - 1 {
            if blue[i][j] == 1 && blue[i][j + 1] == 1 {
                right[i][j] = 1;
            }
        }
    }
    for i in 0..=n - 1 {
        for j in 0..=m {
            if blue[i][j] == 1 && blue[i + 1][j] == 1 {
                up[i][j] = 1;
            }
        }
    }
    make_sum(&mut blue);
    make_sum(&mut right);
    make_sum(&mut up);
    for &(x1, y1, x2, y2) in &queries {
        println!(
            "{}",
            get_sum(&blue, x1, y1, x2, y2)
                - get_sum(&right, x1, y1, x2, y2 - 1)
                - get_sum(&up, x1, y1, x2 - 1, y2)
        )
    }
}
