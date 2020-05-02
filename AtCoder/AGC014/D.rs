use std::io::Read;
use std::collections::HashMap;

fn check(cnt: [usize; 3]) -> usize {
    if cnt[2] > 0 || cnt[1] >= 2 { 2 }
    else if cnt[1] == 0 { 1 }
    else { 0 }
}

#[derive(Default)]
struct Solver {
    all : HashMap<usize, [usize; 3]>,
    part : HashMap<(usize, usize), usize>
}

impl Solver {
    fn solve_impl(&mut self, g: &Vec<Vec<usize>>, pos: usize, prev: usize) -> usize {
        let n = g.len();
        if self.part.contains_key(&(pos, prev)) { return self.part[&(pos, prev)]; }
        if prev != n && self.all.contains_key(&pos){
            let mut cnt = self.all[&pos];
            cnt[self.solve_impl(g, prev, pos)] -= 1;
            let res = check(cnt);
            self.part.insert((pos, prev), res);
            return res;
        }
        let mut cnt = [0; 3];
        for &next in &g[pos] {
            if next == prev { continue; }
            cnt[self.solve_impl(g, next, pos)] += 1;
        }
        let res = check(cnt);
        if prev == n { self.all.insert(pos, cnt); }
        self.part.insert((pos, prev), res);
        res
    }

    pub fn solve(&mut self, g: &Vec<Vec<usize>>) -> bool {
        let n = g.len();
        for i in 0..n {
            if self.solve_impl(g, i, n) == 2 { return true; }
        }
        false
    }
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut it = buf.split_whitespace();
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let mut g = vec![Vec::<usize>::new(); n];
    for _ in 0..n-1 {
        let a = it.next().unwrap().parse::<usize>().unwrap() - 1;
        let b = it.next().unwrap().parse::<usize>().unwrap() - 1;
        g[a].push(b);
        g[b].push(a);
    }
    let mut s = Solver::default();
    println!("{}", if s.solve(&g) { "First" } else { "Second" });
}
