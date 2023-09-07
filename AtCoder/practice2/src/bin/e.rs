use proconio::input;
use std::cmp::Reverse;
use std::collections::BinaryHeap;
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

fn main() {
    input! {
        n: usize, k: Cap,
        a: [[Cost; n];n ]
    }

    const THR: Cost = 1_000_000_000;

    let mut graph = MinCostFlowGraph::new(2 * n + 2);

    graph.add_edge(2 * n, 2 * n + 1, n as Cap * k, THR);

    for i in 0..n {
        graph.add_edge(2 * n, i, k, 0);
        graph.add_edge(n + i, 2 * n + 1, k, 0);
    }
    for i in 0..n {
        for j in 0..n {
            graph.add_edge(i, j + n, 1, THR - a[i][j]);
        }
    }
    println!(
        "{}",
        n as Cost * k as Cost * THR - graph.flow(2 * n, 2 * n + 1, n as Cap * k).1
    );
    for i in 0..n {
        let mut res = vec![false; n];
        for nd in &graph.g[i] {
            if nd.to >= 2 * n || nd.cap > 0 {
                continue;
            }
            res[nd.to - n] = true;
        }
        for b in res {
            print!("{}", if b { 'X' } else { '.' });
        }
        println!("");
    }
}
