use petgraph::unionfind::UnionFind;
use proconio::input;
use proconio::marker::Chars;
use proconio::marker::Usize1;
use rand::seq::SliceRandom;
use rand::thread_rng;
use std::cmp::Reverse;
use std::collections::BinaryHeap;
use std::collections::VecDeque;
use std::i64::MAX;

type Cap = i32;
type Cost = i64;

#[derive(Debug, Clone)]
struct Edge {
    to: usize,
    rev: usize,
    cap: Cap,
    cost: Cost,
}

#[derive(Debug)]
struct MinCostFlowGraph {
    g: Vec<Vec<Edge>>,
}

impl MinCostFlowGraph {
    fn new(n: usize) -> Self {
        Self {
            g: vec![Vec::new(); n],
        }
    }

    fn add_edge(&mut self, from: usize, to: usize, cap: Cap, cost: Cost) {
        let rev_from = self.g[to].len();
        let rev_to = self.g[from].len();
        self.g[from].push(Edge {
            to,
            rev: rev_from,
            cap,
            cost,
        });
        self.g[to].push(Edge {
            to: from,
            rev: rev_to,
            cap: 0,
            cost: -cost,
        });
    }

    fn flow(&mut self, s: usize, t: usize, flow_limit: Cap) -> (Cap, Cost) {
        let n = self.g.len();
        let mut h = vec![0; n];
        let mut dist = vec![0; n];
        let mut prev_v = vec![0; n];
        let mut prev_e = vec![0; n];
        let mut visit = vec![false; n];
        let mut sum_flow = 0;
        let mut sum_cost = 0;
        while sum_flow < flow_limit {
            dist.fill(MAX);
            prev_v.fill(!0);
            prev_e.fill(!0);
            visit.fill(false);
            dist[s] = 0;
            let mut pq: BinaryHeap<Reverse<(Cost, usize)>> = BinaryHeap::new();
            pq.push(Reverse((0, s)));
            while let Some(Reverse((_, v))) = pq.pop() {
                if visit[v] {
                    continue;
                }
                visit[v] = true;
                if v == t {
                    break;
                }
                for (i, e) in self.g[v].iter().enumerate() {
                    if visit[e.to] || e.cap <= 0 {
                        continue;
                    }
                    let cost = e.cost - h[e.to] + h[v];
                    if cost >= dist[e.to] - dist[v] {
                        continue;
                    }
                    dist[e.to] = dist[v] + cost;
                    prev_v[e.to] = v;
                    prev_e[e.to] = i;
                    pq.push(Reverse((dist[e.to], e.to)));
                }
            }
            if !visit[t] {
                break;
            }

            for v in 0..n {
                if !visit[v] {
                    continue;
                }
                h[v] -= dist[t] - dist[v];
            }
            let mut c = flow_limit - sum_flow;
            let mut v = t;
            while v != s {
                c = c.min(self.g[prev_v[v]][prev_e[v]].cap);
                v = prev_v[v];
            }
            v = t;
            while v != s {
                self.g[prev_v[v]][prev_e[v]].cap -= c;
                let rev = self.g[prev_v[v]][prev_e[v]].rev;
                self.g[v][rev].cap += c;
                v = prev_v[v];
            }
            sum_flow += c;
            sum_cost += c as Cost * -h[s];
        }
        (sum_flow, sum_cost)
    }
}

#[derive(Debug)]
pub struct Xorshift {
    seed: u64,
}

impl Xorshift {
    #[allow(dead_code)]
    pub fn new() -> Xorshift {
        Xorshift {
            seed: 0xf0fb588ca2196dac,
        }
    }
    #[inline]
    pub fn next(&mut self) -> u64 {
        self.seed = self.seed ^ (self.seed << 13);
        self.seed = self.seed ^ (self.seed >> 7);
        self.seed = self.seed ^ (self.seed << 17);
        self.seed
    }
    #[inline]
    pub fn rand(&mut self, m: u64) -> u64 {
        self.next() % m
    }
    #[inline]
    #[allow(dead_code)]
    // 0.0 ~ 1.0
    pub fn randf(&mut self) -> f64 {
        use std::mem;
        const UPPER_MASK: u64 = 0x3FF0000000000000;
        const LOWER_MASK: u64 = 0xFFFFFFFFFFFFF;
        let tmp = UPPER_MASK | (self.next() & LOWER_MASK);
        let result: f64 = unsafe { mem::transmute(tmp) };
        result - 1.0
    }
}

#[derive(Debug, Clone)]
struct TreeNode {
    parent: Option<usize>,
    child: Vec<usize>,
}

impl TreeNode {
    #[allow(dead_code)]
    pub fn new() -> TreeNode {
        TreeNode {
            parent: None,
            child: Vec::new(),
        }
    }
}

fn gen_initial_tree(connect: &mut Vec<Vec<bool>>, adj: &Vec<Vec<Option<usize>>>) {
    let mut uf = UnionFind::new(connect.len());
    for i in 0..adj.len() {
        for j in 0..2 {
            if let Some(t) = adj[i][j] {
                if uf.union(i, t) {
                    connect[i][j] = true;
                    connect[t][j + 2] = true;
                }
            }
        }
    }
}

#[allow(dead_code)]
fn gen_initial_tree2(connect: &mut Vec<Vec<bool>>, adj: &Vec<Vec<Option<usize>>>, root: usize) {
    let mut dist = vec![1000000; connect.len()];
    let mut qu = VecDeque::new();
    qu.push_back(root);
    dist[root] = 0;
    let mut uf = UnionFind::new(connect.len());
    while let Some(pos) = qu.pop_front() {
        for i in 0..4 {
            if let Some(t) = adj[pos][i] {
                if dist[t] > dist[pos] + 1 {
                    dist[t] = dist[pos] + 1;
                    if uf.union(t, pos) {
                        connect[pos][i] = true;
                        connect[t][(i + 2) % 4] = true;
                    }
                    qu.push_back(t);
                }
            }
        }
    }
}

fn tree_score(connect: &Vec<Vec<bool>>, adj: &Vec<Vec<Option<usize>>>, root: usize) -> i32 {
    let mut qu = VecDeque::new();
    qu.push_back(root);
    let mut depth = vec![100000; adj.len()];
    depth[root] = 0;
    let mut dec = 0;
    while let Some(cur) = qu.pop_front() {
        let mut leaf = true;
        for i in 0..4 {
            if !connect[cur][i] {
                continue;
            }
            if let Some(t) = adj[cur][i] {
                if depth[t] < depth[cur] {
                    continue;
                }
                depth[t] = depth[cur] + 1;
                qu.push_back(t);
                leaf = false;
            }
        }
        if leaf {
            dec += 1;
        }
    }
    depth.iter().sum::<i32>() - 10 * dec
}

fn improve_tree(
    connect: &mut Vec<Vec<bool>>,
    adj: &Vec<Vec<Option<usize>>>,
    root: usize,
    start_time: &std::time::Instant,
    time_limit: f64,
    initial_temp: f64,
    final_temp: f64,
) {
    let start_sec = start_time.elapsed().as_secs_f64();
    if start_sec >= time_limit {
        return;
    }
    let mut iter_cnt = 0;
    let mut cur_edges = Vec::new();
    let mut all_edges = Vec::new();
    let mut best_score = tree_score(connect, adj, root);
    let mut cur_score = best_score;
    for i in 0..connect.len() {
        for j in 0..2 {
            if connect[i][j] {
                cur_edges.push((i, j));
            }
            if adj[i][j].is_some() {
                all_edges.push((i, j));
            }
        }
    }

    let mut best_edges = cur_edges.clone();
    let mut rnd = Xorshift::new();
    let n = cur_edges.len();
    let mut arr: Vec<usize> = (0..all_edges.len()).collect();
    let mut thread_rng = thread_rng();
    eprintln!("Initial score: {}", best_score);
    loop {
        let cur_sec = start_time.elapsed().as_secs_f64();
        if cur_sec >= time_limit {
            break;
        }
        let rate = (cur_sec - start_sec) / (time_limit - start_sec);
        let temperature = initial_temp + rate * (final_temp - initial_temp);
        let chg = rnd.rand(n as u64) as usize;
        cur_edges.swap(chg, n - 1);
        let last = cur_edges[n - 1];
        connect[last.0][last.1] = false;
        connect[adj[last.0][last.1].unwrap()][last.1 + 2] = false;
        let mut uf = UnionFind::new(connect.len());
        for i in 0..n - 1 {
            uf.union(cur_edges[i].0, adj[cur_edges[i].0][cur_edges[i].1].unwrap());
        }
        arr.shuffle(&mut thread_rng);
        for &a in &arr {
            if uf.union(all_edges[a].0, adj[all_edges[a].0][all_edges[a].1].unwrap()) {
                cur_edges[n - 1].0 = all_edges[a].0;
                cur_edges[n - 1].1 = all_edges[a].1;
                connect[all_edges[a].0][all_edges[a].1] = true;
                connect[adj[all_edges[a].0][all_edges[a].1].unwrap()][all_edges[a].1 + 2] = true;
            }
        }
        let new_score = tree_score(connect, adj, root);
        let diff = new_score as f64 - cur_score as f64;

        if diff < 0.0 || rnd.randf() < (-diff / temperature).exp() {
            cur_score = new_score;
            if cur_score < best_score {
                best_score = cur_score;
                best_edges = cur_edges.clone();
            }
        } else {
            connect[cur_edges[n - 1].0][cur_edges[n - 1].1] = false;
            connect[adj[cur_edges[n - 1].0][cur_edges[n - 1].1].unwrap()][cur_edges[n - 1].1 + 2] =
                false;
            cur_edges[n - 1] = last;
            connect[cur_edges[n - 1].0][cur_edges[n - 1].1] = true;
            connect[adj[cur_edges[n - 1].0][cur_edges[n - 1].1].unwrap()][cur_edges[n - 1].1 + 2] =
                true;
        }
        iter_cnt += 1;
    }
    for i in 0..connect.len() {
        for j in 0..4 {
            connect[i][j] = false;
        }
    }
    for &e in &best_edges {
        connect[e.0][e.1] = true;
        connect[adj[e.0][e.1].unwrap()][e.1 + 2] = true;
    }
    eprintln!("Best score: {}", best_score);
    eprintln!("Iteration for tree: {}", iter_cnt);
}

fn construct_tree(
    h_wall: &Vec<Vec<char>>,
    v_wall: &Vec<Vec<char>>,
    h: usize,
    w: usize,
    root: usize,
    start_time: &std::time::Instant,
    time_limit: f64,
    initial_temp: f64,
    final_temp: f64,
) -> Vec<TreeNode> {
    //   3
    // 2 * 0
    //   1
    let mut adj_idx: Vec<Vec<Option<usize>>> = vec![vec![None; 4]; h * w];
    let mut connect = vec![vec![false; 4]; h * w];
    for i in 0..h - 1 {
        for j in 0..w {
            if h_wall[i][j] == '0' {
                adj_idx[i * w + j][1] = Some(i * w + w + j);
                adj_idx[i * w + w + j][3] = Some(i * w + j);
            }
        }
    }
    for i in 0..h {
        for j in 0..w - 1 {
            if v_wall[i][j] == '0' {
                adj_idx[i * w + j][0] = Some(i * w + j + 1);
                adj_idx[i * w + j + 1][2] = Some(i * w + j);
            }
        }
    }
    gen_initial_tree(&mut connect, &adj_idx);
    improve_tree(
        &mut connect,
        &adj_idx,
        root,
        &start_time,
        time_limit,
        initial_temp,
        final_temp,
    );
    let mut res = vec![TreeNode::new(); w * h];
    let mut qu = VecDeque::new();
    qu.push_back(root);
    while let Some(pos) = qu.pop_front() {
        for i in 0..4 {
            if !connect[pos][i] {
                continue;
            }
            if let Some(t) = adj_idx[pos][i] {
                if adj_idx[pos][i] != res[pos].parent {
                    res[t].parent = Some(pos);
                    res[pos].child.push(t);
                    qu.push_back(t);
                }
            }
        }
    }
    res
}

#[allow(dead_code)]
fn show_tree(tree: &Vec<TreeNode>, h: usize, w: usize) {
    let mut root = 0;
    for i in 0..h * w {
        if tree[i].parent == None {
            root = i;
        }
    }
    let mut res = vec![vec![0; 2 * w]; 2 * h];
    for i in 0..h {
        for j in 0..w {
            res[2 * i][2 * j] = 2;
        }
    }
    let mut qu = VecDeque::new();
    qu.push_back(root);
    while let Some(pos) = qu.pop_back() {
        let y = pos / w * 2;
        let x = pos % w * 2;
        for t in &tree[pos].child {
            qu.push_back(*t);
            if t.abs_diff(pos) == 1 {
                if *t > pos {
                    res[y][x + 1] = 1;
                } else {
                    res[y][x - 1] = 1;
                }
            } else {
                if *t > pos {
                    res[y + 1][x] = 1;
                } else {
                    res[y - 1][x] = 1;
                }
            }
        }
    }
    for i in 0..2 * h - 1 {
        for j in 0..2 * w - 1 {
            if res[i][j] == 0 {
                eprint!(" ");
            } else if res[i][j] == 1 {
                eprint!("+");
            } else {
                eprint!("*")
            }
        }
        eprintln!("");
    }
}

fn get_plants_set(plants_interval: &Vec<(usize, usize)>, t: usize) -> Vec<Vec<Vec<usize>>> {
    let mut res = vec![vec![Vec::new(); t + 1]; t + 1];
    for (i, interval) in plants_interval.iter().enumerate() {
        res[interval.0][interval.1].push(i);
    }
    res
}

fn calc_plants_initial_assign(
    plants_interval: &Vec<(usize, usize)>,
    order: &Vec<usize>,
    t: usize,
    n: usize,
) -> Vec<Vec<usize>> {
    let mut res = vec![Vec::new(); n];
    let plants_set = get_plants_set(&plants_interval, t);
    let mut mcf = MinCostFlowGraph::new(t + 1);
    let mut cap = vec![vec![0; t + 1]; t + 1];
    for i in 0..t {
        cap[i][i + 1] = n as Cap;
        mcf.add_edge(i, i + 1, cap[i][i + 1], 1);
    }
    for i in 0..t {
        for j in i + 2..=t {
            if plants_set[i][j].is_empty() {
                continue;
            }
            cap[i][j] = plants_set[i][j].len() as Cap;
            mcf.add_edge(i, j, cap[i][j], 0);
        }
    }
    let f = mcf.flow(0, t, n as Cap);
    eprintln!("max_flow: {}, {}", f.0, f.1);
    let mut limit = vec![vec![0; t + 1]; t + 1];
    for i in 0..t {
        for nd in &mcf.g[i] {
            if nd.to < i {
                continue;
            }
            limit[i][nd.to] = cap[i][nd.to] - nd.cap;
        }
    }
    let mut sum_flow = 0;
    let mut used = vec![vec![0; t + 1]; t + 1];
    while sum_flow < n as Cap {
        let mut prev = vec![0; t + 1];
        let mut dist = vec![t + 2; t + 1];
        dist[0] = 0;
        for i in 0..t {
            for j in (i + 1..=t).rev() {
                if limit[i][j] == 0 {
                    continue;
                }
                if dist[i] + 1 < dist[j] {
                    dist[j] = dist[i] + 1;
                    prev[j] = i;
                }
            }
        }
        if dist[t] == t + 2 {
            eprintln!("Failed to find all path {}", sum_flow);
        }
        let mut pos = t;
        let mut c = n as Cap;
        while pos != 0 {
            let pre = prev[pos];
            c = c.min(limit[pre][pos]);
            pos = pre;
        }
        pos = t;
        while pos != 0 {
            let pre = prev[pos];
            if pos - pre >= 2 {
                for j in 0..c {
                    res[order[(sum_flow + j) as usize]].push(plants_set[pre][pos][used[pre][pos]]);
                    used[pre][pos] += 1;
                }
            }
            limit[pre][pos] -= c;
            pos = pre;
        }
        for j in 0..c {
            res[order[(sum_flow + j) as usize]].reverse();
        }
        sum_flow += c;
    }
    res
}

fn traverse_tree_dfs(order: &mut Vec<usize>, tree: &Vec<TreeNode>, pos: usize) {
    for t in &tree[pos].child {
        traverse_tree_dfs(order, tree, *t)
    }
    order.push(pos)
}

fn traverse_order(tree: &Vec<TreeNode>, root: usize) -> Vec<usize> {
    let mut res = Vec::new();
    traverse_tree_dfs(&mut res, tree, root);
    res
}

fn inv_order(order: &Vec<usize>) -> Vec<usize> {
    let mut res = vec![0; order.len()];
    for (i, v) in order.iter().enumerate() {
        res[*v] = i;
    }
    res
}

#[allow(dead_code)]
fn show_use_list(list: &Vec<usize>) -> Vec<usize> {
    let t = list.len() - 1;
    let mut res = Vec::new();
    let mut pos = 0;
    res.push(pos);
    while pos != t {
        pos = list[pos];
        res.push(pos);
    }
    res
}

#[allow(dead_code)]
fn same_use_list(a: &Vec<usize>, b: &Vec<usize>) -> bool {
    let t = a.len() - 1;
    let mut pos = 0;
    while pos != t {
        if a[pos] != b[pos] {
            return false;
        }
        pos = a[pos];
    }
    true
}

fn calc_one_cell(
    use_list: &mut Vec<Vec<usize>>,
    node: &TreeNode,
    plants_interval: &Vec<(usize, usize)>,
    current_assign: &Vec<Vec<usize>>,
    valid_plants: &Vec<bool>,
    pos: usize,
    t: usize,
) -> i32 {
    use_list[pos][0] = t;
    for c in &node.child {
        let mut seek_p = 0;
        let mut seek_c = 0;
        while seek_p < t && seek_c < t {
            if use_list[pos][seek_p] >= use_list[*c][seek_c] {
                if use_list[pos][seek_p] > use_list[*c][seek_c] {
                    let next = use_list[*c][seek_c];
                    use_list[pos][next] = use_list[pos][seek_p];
                    use_list[pos][seek_p] = next;
                }
                seek_c = use_list[*c][seek_c];
            }
            seek_p = use_list[pos][seek_p];
        }
    }
    let mut res = 0;
    let mut p_src = 0;
    let mut p_dst = use_list[pos][0];
    for &plant in &current_assign[pos] {
        if !valid_plants[plant] {
            continue;
        }
        let interval = &plants_interval[plant];
        while p_dst <= interval.0 {
            p_src = p_dst;
            p_dst = use_list[pos][p_src];
        }
        if p_src <= interval.0 && interval.1 <= p_dst {
            res += (interval.1 - interval.0) as i32;
            if interval.1 < p_dst {
                use_list[pos][interval.1] = p_dst;
                use_list[pos][p_src] = interval.1;
                p_src = interval.1;
            }
        }
    }
    res
}

fn calc_score_full(
    tree: &Vec<TreeNode>,
    order: &Vec<usize>,
    plants_interval: &Vec<(usize, usize)>,
    current_assign: &Vec<Vec<usize>>,
    valid_plants: &Vec<bool>,
    n: usize,
    t: usize,
) -> (Vec<Vec<usize>>, Vec<i32>, i32) {
    let mut use_list = vec![vec![0; t + 1]; n];
    let mut scores = vec![0; n];
    for idx in order {
        scores[*idx] = calc_one_cell(
            &mut use_list,
            &tree[*idx],
            plants_interval,
            current_assign,
            valid_plants,
            *idx,
            t,
        );
    }
    let sum_score = scores.iter().sum();
    (use_list, scores, sum_score)
}

fn update_one_cell(
    use_list: &mut Vec<Vec<usize>>,
    use_list_keep: &mut Vec<Vec<usize>>,
    scores: &mut Vec<i32>,
    scores_keep: &mut Vec<i32>,
    node: &TreeNode,
    plants_interval: &Vec<(usize, usize)>,
    current_assign: &Vec<Vec<usize>>,
    valid_plants: &Vec<bool>,
    pos: usize,
    t: usize,
) -> i32 {
    std::mem::swap(&mut use_list[pos], &mut use_list_keep[pos]);
    std::mem::swap(&mut scores[pos], &mut scores_keep[pos]);
    scores[pos] = calc_one_cell(
        use_list,
        node,
        plants_interval,
        current_assign,
        valid_plants,
        pos,
        t,
    );
    scores[pos] - scores_keep[pos]
}

fn rollback_one_cell(
    use_list: &mut Vec<Vec<usize>>,
    use_list_keep: &mut Vec<Vec<usize>>,
    scores: &mut Vec<i32>,
    scores_keep: &mut Vec<i32>,
    pos: usize,
) {
    std::mem::swap(&mut use_list[pos], &mut use_list_keep[pos]);
    std::mem::swap(&mut scores[pos], &mut scores_keep[pos]);
}

fn update_one_path(
    use_list: &mut Vec<Vec<usize>>,
    use_list_keep: &mut Vec<Vec<usize>>,
    scores: &mut Vec<i32>,
    scores_keep: &mut Vec<i32>,
    tree: &Vec<TreeNode>,
    plants_interval: &Vec<(usize, usize)>,
    current_assign: &Vec<Vec<usize>>,
    valid_plants: &Vec<bool>,
    pos: usize,
    t: usize,
) -> i32 {
    let mut res = 0;
    let mut p0 = pos;
    loop {
        res += update_one_cell(
            use_list,
            use_list_keep,
            scores,
            scores_keep,
            &tree[p0],
            plants_interval,
            current_assign,
            valid_plants,
            p0,
            t,
        );
        if scores[p0] == scores_keep[p0] && same_use_list(&use_list[p0], &use_list_keep[p0]) {
            break;
        }
        if let Some(t) = tree[p0].parent {
            p0 = t;
        } else {
            break;
        }
    }
    res
}

fn rollback_one_path(
    use_list: &mut Vec<Vec<usize>>,
    use_list_keep: &mut Vec<Vec<usize>>,
    scores: &mut Vec<i32>,
    scores_keep: &mut Vec<i32>,
    tree: &Vec<TreeNode>,
    pos: usize,
) {
    let mut p0 = pos;
    loop {
        if scores[p0] == scores_keep[p0] && same_use_list(&use_list[p0], &use_list_keep[p0]) {
            break;
        }
        rollback_one_cell(use_list, use_list_keep, scores, scores_keep, p0);
        if let Some(t) = tree[p0].parent {
            p0 = t;
        } else {
            break;
        }
    }
}

fn update_two_path(
    use_list: &mut Vec<Vec<usize>>,
    use_list_keep: &mut Vec<Vec<usize>>,
    scores: &mut Vec<i32>,
    scores_keep: &mut Vec<i32>,
    tree: &Vec<TreeNode>,
    idx_to_order: &Vec<usize>,
    plants_interval: &Vec<(usize, usize)>,
    current_assign: &Vec<Vec<usize>>,
    valid_plants: &Vec<bool>,
    pos0: usize,
    pos1: usize,
    t: usize,
) -> i32 {
    let mut p0 = pos0;
    let mut p1 = pos1;
    let mut res = 0;
    while p0 != p1 {
        if idx_to_order[p0] < idx_to_order[p1] {
            res += update_one_cell(
                use_list,
                use_list_keep,
                scores,
                scores_keep,
                &tree[p0],
                plants_interval,
                current_assign,
                valid_plants,
                p0,
                t,
            );
            if scores[p0] == scores_keep[p0] && same_use_list(&use_list[p0], &use_list_keep[p0]) {
                p0 = p1;
                break;
            }
            p0 = tree[p0].parent.unwrap();
        } else {
            res += update_one_cell(
                use_list,
                use_list_keep,
                scores,
                scores_keep,
                &tree[p1],
                plants_interval,
                current_assign,
                valid_plants,
                p1,
                t,
            );
            if scores[p1] == scores_keep[p1] && same_use_list(&use_list[p1], &use_list_keep[p1]) {
                break;
            }

            p1 = tree[p1].parent.unwrap();
        }
    }
    res + update_one_path(
        use_list,
        use_list_keep,
        scores,
        scores_keep,
        tree,
        plants_interval,
        current_assign,
        valid_plants,
        p0,
        t,
    )
}

fn rollback_two_path(
    use_list: &mut Vec<Vec<usize>>,
    use_list_keep: &mut Vec<Vec<usize>>,
    scores: &mut Vec<i32>,
    scores_keep: &mut Vec<i32>,
    tree: &Vec<TreeNode>,
    idx_to_order: &Vec<usize>,
    pos0: usize,
    pos1: usize,
) {
    let mut p0 = pos0;
    let mut p1 = pos1;
    while p0 != p1 {
        if idx_to_order[p0] < idx_to_order[p1] {
            if scores[p0] == scores_keep[p0] && same_use_list(&use_list[p0], &use_list_keep[p0]) {
                p0 = p1;
                break;
            }
            rollback_one_cell(use_list, use_list_keep, scores, scores_keep, p0);
            p0 = tree[p0].parent.unwrap();
        } else {
            if scores[p1] == scores_keep[p1] && same_use_list(&use_list[p1], &use_list_keep[p1]) {
                break;
            }
            rollback_one_cell(use_list, use_list_keep, scores, scores_keep, p1);
            p1 = tree[p1].parent.unwrap();
        }
    }
    rollback_one_path(use_list, use_list_keep, scores, scores_keep, tree, p0)
}

fn solve(
    tree: &Vec<TreeNode>,
    plants_interval: &Vec<(usize, usize)>,
    root: usize,
    t: usize,
    n: usize,
    start_time: &std::time::Instant,
    time_limit: f64,
    initial_temp: f64,
    final_temp: f64,
) -> Vec<(usize, usize, usize)> {
    let order = traverse_order(tree, root);
    let idx_to_order = inv_order(&order);
    let initial_assign = calc_plants_initial_assign(&plants_interval, &order, t, n);
    let mut valid_plants = vec![true; plants_interval.len()];
    let (mut use_list, mut scores, mut cur_score) = calc_score_full(
        tree,
        &order,
        plants_interval,
        &initial_assign,
        &valid_plants,
        n,
        t,
    );
    eprintln!("Initial score: {}", cur_score);
    let mut use_list_keep = vec![vec![0; t + 1]; n];
    let mut scores_keep = scores.clone();
    let mut current_assign = initial_assign.clone();
    // initial_assign で i 番目にいた割り当てが、いまどこにいるかを表す
    // swap操作は assign_ref[i0] と assign_ref[i1] に対して行う
    let mut assign_ref = (0..initial_assign.len()).collect::<Vec<usize>>();
    let mut plants_assign = vec![0; plants_interval.len()];
    // assign_ref[plants_assign[plants_idx]] で、plants_idxが今属するセルの番号を取る
    for (i, ass) in initial_assign.iter().enumerate() {
        for a in ass {
            plants_assign[*a] = i
        }
    }
    let mut valid_list = Vec::new();
    let mut invalid_list = Vec::new();
    for arr in &initial_assign {
        for v in arr {
            valid_list.push(*v);
        }
    }
    let mut rnd = Xorshift::new();
    let mut iter_cnt = 0;
    let start_sec = start_time.elapsed().as_secs_f64();
    loop {
        let cur_sec = start_time.elapsed().as_secs_f64();
        if cur_sec >= time_limit {
            break;
        }
        let rate = (cur_sec - start_sec) / (time_limit - start_sec);
        let temperature = initial_temp + rate * (final_temp - initial_temp);
        let try_type = rnd.rand(4) + 12;
        if try_type < 16 {
            let mut i0 = rnd.rand(n as u64) as usize;
            let mut i1 = rnd.rand(n as u64) as usize;
            while i0 == i1 {
                i0 = rnd.rand(n as u64) as usize;
                i1 = rnd.rand(n as u64) as usize;
            }
            let p0 = assign_ref[i0];
            let p1 = assign_ref[i1];
            current_assign.swap(p0, p1);
            assign_ref.swap(i0, i1);
            let diff = update_two_path(
                &mut use_list,
                &mut use_list_keep,
                &mut scores,
                &mut scores_keep,
                tree,
                &idx_to_order,
                plants_interval,
                &current_assign,
                &valid_plants,
                p0,
                p1,
                t,
            );
            let diff_f64 = diff as f64;
            if diff_f64 > 0.0 || rnd.randf() < (diff_f64 / temperature).exp() {
                cur_score += diff;
            } else {
                current_assign.swap(p0, p1);
                assign_ref.swap(i0, i1);
                rollback_two_path(
                    &mut use_list,
                    &mut use_list_keep,
                    &mut scores,
                    &mut scores_keep,
                    tree,
                    &idx_to_order,
                    p0,
                    p1,
                )
            }
        } else {
            let add = valid_list.is_empty() || (!invalid_list.is_empty() && try_type == 14);
            let chg_idx = rnd.rand(if add {
                invalid_list.len()
            } else {
                valid_list.len()
            } as u64) as usize;
            let target_plant = if add {
                invalid_list[chg_idx]
            } else {
                valid_list[chg_idx]
            };
            valid_plants[target_plant] = add;
            let p0 = assign_ref[plants_assign[target_plant]];
            let diff = update_one_path(
                &mut use_list,
                &mut use_list_keep,
                &mut scores,
                &mut scores_keep,
                tree,
                plants_interval,
                &current_assign,
                &valid_plants,
                p0,
                t,
            );
            let diff_f64 = diff as f64;
            if diff_f64 > 0.0 || rnd.randf() < (diff_f64 / temperature).exp() {
                cur_score += diff;
                if add {
                    valid_list.push(target_plant);
                    let back_idx = invalid_list.len() - 1;
                    invalid_list.swap(chg_idx, back_idx);
                    invalid_list.pop();
                } else {
                    invalid_list.push(target_plant);
                    let back_idx = valid_list.len() - 1;
                    valid_list.swap(chg_idx, back_idx);
                    valid_list.pop();
                }
            } else {
                valid_plants[target_plant] = !add;
                rollback_one_path(
                    &mut use_list,
                    &mut use_list_keep,
                    &mut scores,
                    &mut scores_keep,
                    tree,
                    p0,
                )
            }
        }
        iter_cnt += 1;
    }
    eprintln!("Cur score: {}", cur_score);
    eprintln!("Iteration for tree: {}", iter_cnt);
    let mut used_plants = vec![false; plants_interval.len()];
    let mut used_interval = vec![vec![false; t + 1]; n];
    let mut result = Vec::new();
    for i in 0..n {
        let mut cur = 0;
        let mut next = use_list[i][0];
        for p in &current_assign[i] {
            while next < plants_interval[*p].1 {
                cur = next;
                next = use_list[i][cur];
            }
            if next == plants_interval[*p].1 && cur <= plants_interval[*p].0 {
                result.push((*p + 1, i, cur + 1));
                used_plants[*p] = true;
                used_interval[i][next] = true;
            }
        }
    }
    let mut unused_plants = vec![vec![Vec::new(); t + 1]; t + 1];
    for (i, pi) in plants_interval.iter().enumerate() {
        if used_plants[i] {
            continue;
        }
        unused_plants[pi.0][pi.1].push(i);
    }
    let mut added_score = 0;
    for i in 0..n {
        let mut cur = 0;
        let mut next = use_list[i][0];
        loop {
            if !used_interval[i][next] {
                for j in cur..next {
                    if !unused_plants[j][next].is_empty() {
                        added_score += next - j;
                        result.push((unused_plants[j][next].pop().unwrap() + 1, i, cur + 1));
                        break;
                    }
                }
            }
            if next == t {
                break;
            }
            cur = next;
            next = use_list[i][cur];
        }
    }
    eprintln!("{}", added_score);
    result
}

fn main() {
    let start_time = std::time::Instant::now();
    input! {
        t: usize, h: usize, w:usize, i0: usize,
        h_wall: [Chars; h-1],
        v_wall: [Chars; h],
        k: usize,
        plants_interval: [(Usize1, usize); k]
    }
    let tree = construct_tree(
        &h_wall,
        &v_wall,
        h,
        w,
        i0 * w,
        &start_time,
        0.25,
        8.30583545083,
        0.21714724095,
    );
    // show_tree(&tree, h, w);
    let res = solve(
        &tree,
        &plants_interval,
        i0 * w,
        t,
        h * w,
        &start_time,
        1.8,
        8.30583545083,
        0.21714724095,
    );
    println!("{}", res.len());
    for a in res {
        println!("{} {} {} {}", a.0, a.1 / w, a.1 % w, a.2);
    }
}
