use proconio::input;

fn solve(g : &Vec<Vec<usize>>, a : &Vec<u32>,
         pos : usize, prev : usize, best : usize,
         res : &mut Vec<usize>, inc : &mut Vec<u32>)
{
    let n = g.len();
    let idx = if a[pos] <= inc[0] {
        0
    } else {
        let mut low = 0;
        let mut high = n-1;
        while high - low > 1 {
            let mid = (low+high)/2;
            if a[pos] <= inc[mid] {
                high = mid;
            } else {
                low = mid;
            }
        }
        high
    };
    let cur_value = inc[idx];
    inc[idx] = a[pos];
    res[pos] = best.max(idx + 1);
    for &next in &g[pos] {
        if next == prev { continue; }
        solve(g, a, next, pos, best.max(idx+1), res, inc);
    }
    inc[idx] = cur_value;
}

fn main() {
    input! {
        n : usize,
        a : [u32; n]
    };
    let mut g = vec![Vec::new(); n];
    for _ in 0..n-1 {
        input! {
            (u, v) : (usize, usize)
        };
        g[u-1].push(v-1);
        g[v-1].push(u-1);
    }
    let mut res = vec![1; n];
    let mut inc = vec![1_000_000_007; n];
    solve(&g, &a, 0, n, 1, &mut res, &mut inc);
    for r in res { println!("{}", r); }
}
