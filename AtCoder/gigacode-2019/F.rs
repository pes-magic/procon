fn main() {
    proconio::input! {
        h: usize,
        w: usize,
        n: usize,
        block: [(usize, usize); n]
    }
    let mut field = vec![vec![0; w+1]; h+2];
    for i in 1..=h {
        for j in 0..w { field[i][j] = 1 }
    }
    for &p in &block { field[p.0][p.1-1] = 0 }
    for i in 0..w {
        for j in (1..=h).rev() {
            if field[j][i] == 0 { continue }
            field[j][i] += field[j+1][i];
        }
    }
    let mut res = 0;
    let mut low = vec![0; w+2];
    let mut st = Vec::<(i32, usize)>::new();
    for i in 1..=h {
        for j in 0..=w {
            low[j+1] = 1 - field[i-1][j].min(1) + low[j];
            let mut left = j;
            while !st.is_empty() && st.last().unwrap().0 > field[i][j] {
                left = st.last().unwrap().1;
                if low[j] - low[left] > 0 { res += 1 }
                st.pop();
            }
            if field[i][j] > 0 && (st.is_empty() || st.last().unwrap().0 < field[i][j]) {
                st.push((field[i][j], left));
            }
        }
    }
    println!("{}", res);
}
