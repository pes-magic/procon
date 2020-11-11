fn main() {
    proconio::input! {
        h: usize,
        w: usize,
        n: usize,
        m: usize,
        light: [(usize, usize); n],
        block: [(usize, usize); m]
    }
    let mut b = vec![vec![0; w+2]; h+2];
    let mut visit = vec![vec![0; w+2]; h+2];
    for &p in &light {
        b[p.0][p.1] = 1
    }
    for &p in &block {
        b[p.0][p.1] = 1
    }
    for i in 0..=w+1 {
        b[0][i] = 1;
        b[h+1][i] = 1;
    }
    for i in 0..=h+1 {
        b[i][0] = 1;
        b[i][w+1] = 1;
    }
    let dir = [(!0, 0), (0, !0), (1, 0), (0, 1)];
    for &l in &light {
        for &d in &dir {
            let mut x = l.0.wrapping_add(d.0);
            let mut y = l.1.wrapping_add(d.1);
            while b[x][y] == 0 {
                visit[x][y] = 1;
                x = x.wrapping_add(d.0);
                y = y.wrapping_add(d.1);
            }
        }
    }
    let mut res = n;
    for v in &visit {
        res += v.iter().sum::<usize>();
    }
    println!("{}", res);
}

