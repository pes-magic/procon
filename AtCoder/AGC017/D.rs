use std::io::Read;

fn solve(g : &Vec<Vec<usize>>, pos : usize, prev : usize) -> u32 {
    let mut res = 0;
    for &t in &g[pos] {
        if t == prev { continue }
        res ^= solve(g, t, pos) + 1;
    }
    res
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut g = vec![Vec::new(); n];
    for _ in 0..n-1 {
        let x = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let y = it.next().unwrap().parse::<usize>().unwrap() - 1;
        g[x].push(y);
        g[y].push(x);
    }
    println!("{}", if solve(&g, 0, n) != 0 { "Alice" } else { "Bob" });
}
