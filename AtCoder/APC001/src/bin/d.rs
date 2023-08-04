use petgraph::unionfind::UnionFind;
use proconio::input;

fn main() {
    input! {
        n: usize, m: usize,
        a: [i64; n],
        edges: [(usize, usize); m]
    }
    let mut uf = UnionFind::<usize>::new(n);
    for &(x, y) in &edges {
        uf.union(x, y);
    }
    let mut vecs = vec![Vec::new(); n];
    for (i, &val) in a.iter().enumerate() {
        vecs[uf.find(i)].push(val);
    }
    let mut mins = Vec::new();
    let mut all = Vec::new();
    for vec in &mut vecs {
        if vec.is_empty() {
            continue;
        }
        vec.sort();
        mins.push(vec[0]);
        all.extend(vec[1..].to_vec());
    }
    if mins.len() == 1 {
        println!("0");
        return;
    }
    if all.len() + 2 < mins.len() {
        println!("Impossible");
        return;
    }
    all.sort();
    let res = mins.iter().sum::<i64>() + all[..mins.len() - 2].iter().sum::<i64>();
    println!("{}", res);
}
