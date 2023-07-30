use itertools::enumerate;
use proconio::input;
use proconio::marker::Usize1;

fn main() {
    input! {
        n:usize, m:usize,
        edges: [(Usize1,Usize1);m],
        q:usize,
        queries:[(Usize1,usize,usize);q]
    }
    let mut g = vec![Vec::new(); n];
    for &e in &edges {
        g[e.0].push(e.1);
        g[e.1].push(e.0);
    }
    let mut color = vec![vec![0; 11]; n];
    let mut updated = vec![vec![0; 11]; n];
    for target_dist in (0..=10).rev() {
        for (i, query) in enumerate(&queries) {
            if query.1 != target_dist {
                continue;
            }
            if updated[query.0][target_dist] < i + 1 {
                updated[query.0][target_dist] = i + 1;
                color[query.0][target_dist] = query.2;
            }
        }
        if target_dist != 0 {
            for i in 0..n {
                if updated[i][target_dist] != 0 {
                    for &pos in &g[i] {
                        if updated[pos][target_dist - 1] < updated[i][target_dist] {
                            updated[pos][target_dist - 1] = updated[i][target_dist];
                            color[pos][target_dist - 1] = color[i][target_dist];
                        }
                    }
                }
            }
        }
    }
    for i in 0..n {
        let latest = updated[i].iter().max().unwrap();
        for j in 0..=10 {
            if updated[i][j] == *latest {
                println!("{}", color[i][j]);
                break;
            }
        }
    }
}
