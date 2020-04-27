use proconio::input;

fn solve_inner(row: &Vec<u64>, col: &Vec<u64>) -> Option<Vec<Vec<u64>>> {
    let n = row.len();
    // o : at least one element is 0
    // 1 : all elements are 1
    // 2 : all elements are 0
    // 3 : at least one element is 1
    let mut row_cnt = [0; 4];
    let mut col_cnt = [0; 4];
    for i in 0..n {
        row_cnt[row[i] as usize] += 1;
        col_cnt[col[i] as usize] += 1;
    }
    if row_cnt[1] == n || (n == 1 && row_cnt[3] == n) {
        if col_cnt[1] + col_cnt[3] == n { return Some(vec![vec![1; n]; n]) }
    } else if row_cnt[2] == n || (n == 1 && row_cnt[0] == n) {
        if col_cnt[0] + col_cnt[2] == n { return Some(vec![vec![0; n]; n]) }
    } else if col_cnt[1] == n || (n == 1 && col_cnt[3] == n) {
        if row_cnt[1] + row_cnt[3] == n { return Some(vec![vec![1; n]; n]) }
    } else if col_cnt[2] == n || (n == 1 && col_cnt[0] == n) {
        if row_cnt[0] + row_cnt[2] == n { return Some(vec![vec![0; n]; n]) }
    } else if (row_cnt[1] == 0 || col_cnt[2] == 0) && (row_cnt[2] == 0 || col_cnt[1] == 0) {
        let mut res = vec![vec![0; n]; n];
        if (row_cnt[1] > 0 && row_cnt[2] == 0 && col_cnt[1] > 0 && col_cnt[2] == 0) ||
            (row_cnt[1] == n-1 && row_cnt[0] == 1 && col_cnt[1] + col_cnt[2] == 0) ||
            (col_cnt[1] == n-1 && col_cnt[0] == 1 && row_cnt[1] + row_cnt[2] == 0)
        {
            for i in 0..n {
                for j in 0..n {
                    res[i][j] = if row[i] == 1 || col[j] == 1 { 1 } else { 0 }
                }
            }
        } else if (row_cnt[2] > 0 && row_cnt[1] == 0 && col_cnt[2] > 0 && col_cnt[1] == 0) ||
            (row_cnt[2] == n-1 && row_cnt[3] == 1 && col_cnt[1] + col_cnt[2] == 0) ||
            (col_cnt[2] == n-1 && col_cnt[3] == 1 && row_cnt[1] + row_cnt[2] == 0)
        {
            for i in 0..n {
                for j in 0..n {
                    res[i][j] = if row[i] == 2 || col[j] == 2 { 0 } else { 1 }
                }
            }
        } else if row_cnt[1] == n-1 && row_cnt[3] == 1 {
            if col_cnt[0] == n { return None; }
            for i in 0..n {
                for j in 0..n {
                    res[i][j] = if row[i] == 1 || col[j] != 0  { 1 } else { 0 }
                }
            }
        } else if col_cnt[1] == n-1 && col_cnt[3] == 1 {
            if row_cnt[0] == n { return None; }
            for i in 0..n {
                for j in 0..n {
                    res[i][j] = if col[j] == 1 || row[i] != 0  { 1 } else { 0 }
                }
            }
        } else if row_cnt[2] == n-1 && row_cnt[0] == 1 {
            if col_cnt[3] == n { return None; }
            for i in 0..n {
                for j in 0..n {
                    res[i][j] = if row[i] == 2 || col[j] != 3  { 0 } else { 1 }
                }
            }
        } else if col_cnt[2] == n-1 && col_cnt[0] == 1 {
            if row_cnt[3] == n { return None; }
            for i in 0..n {
                for j in 0..n {
                    res[i][j] = if col[j] == 2 || row[i] != 3  { 0 } else { 1 }
                }
            }
        } else {
            let mut ci = 0;
            for i in 0..n {
                let mut cj = 0;
                for j in 0..n {
                    res[i][j] = if row[i] == 1 || col[j] == 1 { 1 } else if row[i] == 2 || col[j] == 2 { 0 } else { cj += 1; (ci+cj)%2 }
                }
                if row[i] == 0 || row[i] == 3 { ci += 1; }
            }
        }
        return Some(res);
    }
    None
}

fn solve(s: &Vec<u64>, t: &Vec<u64>, u: &Vec<u64>, v: &Vec<u64>) -> Option<Vec<Vec<u64>>> {
    let n = s.len();
    let mut res = vec![vec![0; n]; n];
    let mut row = vec![0; n];
    let mut col = vec![0; n];
    for i in 0..64 {
        for j in 0..n {
            row[j] = 2 * s[j] + (u[j] >> i) % 2;
            col[j] = 2 * t[j] + (v[j] >> i) % 2;
        }
        if let Some(part_res) = solve_inner(&row, &col) {
            for j in 0..n {
                for k in 0..n {
                    res[j][k] |= part_res[j][k] << i;
                }
            }
        } else {
            return None;
        }
    }
    Some(res)
}

fn main(){
    input! {
        n : usize,
        s : [u64; n],
        t : [u64; n],
        u : [u64; n],
        v : [u64; n]
    };
    if let Some(res) = solve(&s, &t, &u, &v) {
        for a in res {
            print!("{}", a[0]);
            for i in 1..n { print!(" {}", a[i]); }
            println!("");
        }
    } else {
        println!("-1");
    }
}