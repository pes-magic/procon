use num_traits::Pow;

struct XorShift {
    x: u32,
    y: u32,
    z: u32,
    w: u32,
}

impl XorShift {
    fn new(seed: u32) -> XorShift {
        let mut rng = XorShift {
            x: seed,
            y: 0,
            z: 0,
            w: 0,
        };
        rng.init(seed);
        rng
    }

    fn init(&mut self, seed: u32) {
        self.x = 1812433253u32
            .wrapping_mul(seed ^ (seed >> 30))
            .wrapping_add(1);
        self.y = 1812433253u32
            .wrapping_mul(self.x ^ (self.x >> 30))
            .wrapping_add(2);
        self.z = 1812433253u32
            .wrapping_mul(self.y ^ (self.y >> 30))
            .wrapping_add(3);
        self.w = 1812433253u32
            .wrapping_mul(self.z ^ (self.z >> 30))
            .wrapping_add(4);
    }

    fn rand(&mut self) -> u32 {
        let t = self.x ^ (self.x << 11);
        self.x = self.y;
        self.y = self.z;
        self.z = self.w;
        self.w = (self.w ^ (self.w >> 19)) ^ (t ^ (t >> 8));
        self.w
    }

    fn gen_range(&mut self, src: u32, dst: u32) -> u32 {
        self.rand() % (dst - src) + src
    }
}

fn calc_needed_height(w: usize, a: &Vec<i32>, idx: &Vec<usize>) -> usize {
    if idx.is_empty() {
        return 0;
    }
    let mut sum = 0;
    for v in idx {
        sum += a[*v] as usize;
    }
    let mut h = (sum + w - 1) / w;
    loop {
        let mut sum_w = 0;
        for v in idx {
            sum_w += (a[*v] as usize + h - 1) / h;
            if sum_w > w {
                break;
            }
        }
        if sum_w <= w {
            break;
        }
        h += 1;
    }
    h
}

fn merge_days(a: Vec<Vec<i32>>, w: usize) -> Vec<(Vec<i32>, usize)> {
    let mut dp = vec![(a.len() as i32 + 2, 0); a.len() + 1];
    dp[0] = (0, 0);
    let mut prev = vec![0; a.len() + 1];
    let mut ret = Vec::new();
    let mut count = Vec::new();
    let upper_sum = w.pow(2) as i32 - 5000;

    for i in 0..a.len() {
        let mut mx = a[i].clone();
        for j in i..a.len() {
            for (k, &val) in a[j].iter().enumerate() {
                mx[k] = mx[k].max(val);
            }
            let sum: i32 = mx.iter().sum();
            if i != j && sum > upper_sum {
                break;
            }
            let next_step = dp[i].0 + 1;
            let next_cost = dp[i].1 + sum as i32;
            if dp[j + 1] > (next_step, next_cost) {
                dp[j + 1] = (next_step, next_cost);
                prev[j + 1] = i;
            }
        }
    }

    let mut cur = a.len();
    while cur > 0 {
        let pre = prev[cur as usize];
        let mut mx = a[pre as usize].clone();
        for i in pre as usize..cur as usize {
            for (j, &val) in a[i].iter().enumerate() {
                mx[j] = mx[j].max(val);
            }
        }
        ret.push(mx);
        count.push(cur - pre);
        cur = pre;
    }

    ret.reverse();
    count.reverse();

    (0..ret.len()).map(|i| (ret[i].clone(), count[i])).collect()
}

pub fn get_time() -> f64 {
    static mut STIME: f64 = -1.0;
    let t = std::time::SystemTime::now()
        .duration_since(std::time::UNIX_EPOCH)
        .unwrap();
    let ms = t.as_secs() as f64 + t.subsec_nanos() as f64 * 1e-9;
    unsafe {
        if STIME < 0.0 {
            STIME = ms;
        }
        // ローカル環境とジャッジ環境の実行速度差はget_timeで吸収しておくと便利
        #[cfg(feature = "local")]
        {
            (ms - STIME) * 1.0
        }
        #[cfg(not(feature = "local"))]
        {
            ms - STIME
        }
    }
}

//------------------------------------------------------------------------------
fn print_rectangle(state: &Vec<Vec<usize>>, heights: &Vec<usize>, a: &Vec<i32>, w: usize) {
    let mut cur_h = 0;

    let mut rect = Vec::new();

    for i in 0..heights.len() {
        let h = heights[i];
        let next_h = h + cur_h;
        let mut cur_w = 0;
        for j in 0..state[i].len() {
            let width = (a[state[i][j]] as usize + h - 1) / h;
            let next_w = if j == state[i].len() - 1 {
                w
            } else {
                w.min(cur_w + width)
            };
            rect.push((state[i][j], (cur_w, cur_h, next_w, next_h)));
            cur_w = next_w;
        }
        cur_h = next_h;
    }
    rect.sort_by_key(|k| k.0);

    for (_, (v_prev, h_prev, v, h)) in rect {
        println!("{} {} {} {}", v_prev, h_prev, v, h);
    }
}

//------------------------------------------------------------------------------
fn gen_heights(state: &Vec<Vec<usize>>, a: &Vec<i32>, w: usize) -> Vec<usize> {
    let mut cur_h = 0;
    let mut size = state.len();
    for i in 0..state.len() {
        if state[i].is_empty() {
            size = i;
            break;
        }
    }

    let mut heights = Vec::new();
    for i in 0..size {
        heights.push(calc_needed_height(w, a, &state[i]));
    }
    let h_sum = heights.iter().sum::<usize>();
    if h_sum > w {
        let mut rnd = XorShift::new(1234567891);
        for i in w..h_sum {
            loop {
                let l = rnd.gen_range(0, heights.len() as u32) as usize;
                if heights[l] >= 2 {
                    heights[l] -= 1;
                    break;
                }
            }
        }
    }
    heights
}

//------------------------------------------------------------------------------

fn calc_best_heights(
    lined: &Vec<bool>,
    base_heights: &Vec<usize>,
    sum_h: usize,
) -> (usize, Vec<usize>) {
    let w = lined.len();
    let n = base_heights.len();
    let mut dp = vec![vec![0; w - sum_h + 1]; n];
    let mut prev = vec![vec![(0, 0); w - sum_h + 1]; n];
    let mut base_sum = vec![0; base_heights.len()];
    base_sum[0] = base_heights[0];
    for i in 1..base_heights.len() {
        base_sum[i] = base_sum[i - 1] + base_heights[i];
    }
    for i in 0..w - sum_h {
        prev[n - 1][i] = (n - 1, i + 1);
    }
    for i in (0..n - 1).rev() {
        for j in (0..=w - sum_h).rev() {
            if lined[base_sum[i] + j] {
                dp[i][j] = dp[i + 1][j] + 1;
                prev[i][j] = (i + 1, j);
            }
            if dp[i][j] <= dp[i + 1][j] {
                dp[i][j] = dp[i + 1][j];
                prev[i][j] = (i + 1, j);
            }
            if j + 1 <= w - sum_h && dp[i][j] <= dp[i][j + 1] {
                dp[i][j] = dp[i][j + 1];
                prev[i][j] = (i, j + 1);
            }
        }
    }
    let mut pj = 0;
    let mut res = base_heights.clone();
    for i in 0..n {
        while prev[i][pj].0 == i {
            pj += 1;
            res[i] += 1;
        }
    }
    (dp[0][0], res)
}

//------------------------------------------------------------------------------
fn main() {
    let initial_temp = 1000.0;
    let final_temp = 0.0;
    let time_limit = 2.970;
    // load W, D, N from one line using proconio
    proconio::input! {w: usize, d: usize, n: usize};
    proconio::input! {a: [[i32; n]; d]};

    let mut rnd = XorShift::new(1234567891);
    let r = merge_days(a, w);
    let d = r.len();
    let mut states = vec![vec![Vec::new(); n]; d];
    for i in 0..d {
        for j in 0..n {
            states[i][j].push(j);
        }
    }
    let mut state_size = vec![n; d];
    let mut best_states = states.clone();
    let mut it_count = 0;
    let mut cur_time = get_time();
    for (day, (a, _)) in r.iter().enumerate() {
        let timer_start = cur_time;
        let timer_end = 0.7 * time_limit / d as f64 * (day + 1) as f64;
        let mut cur_height = vec![0; n];
        for i in 0..n {
            cur_height[i] = calc_needed_height(w, &a, &states[day][i]);
        }
        let mut cur_score = cur_height.iter().sum::<usize>();
        let mut best_score = cur_score;
        let mut state = &mut states[day];
        while cur_time < timer_end {
            it_count += 1;
            let mut swp_a0 = !0;
            let mut swp_a1 = !0;
            let mut swp_b0 = !0;
            let mut swp_b1 = !0;
            let size = state_size[day];
            if rnd.rand() % 4 != 0 && size >= 2 {
                loop {
                    assert!(size >= 1);
                    swp_a0 = rnd.gen_range(0, size as u32) as usize;
                    swp_b0 = rnd.gen_range(0, size as u32) as usize;
                    if swp_a0 == swp_b0 {
                        continue;
                    }
                    assert!(!state[swp_a0].is_empty());
                    assert!(!state[swp_b0].is_empty());
                    swp_a1 = rnd.gen_range(0, state[swp_a0].len() as u32) as usize;
                    swp_b1 = rnd.gen_range(0, state[swp_b0].len() as u32) as usize;
                    let v0 = state[swp_a0][swp_a1];
                    let v1 = state[swp_b0][swp_b1];
                    state[swp_a0][swp_a1] = v1;
                    state[swp_b0][swp_b1] = v0;
                    break;
                }
            } else {
                loop {
                    assert!(size >= 1);
                    swp_a0 = rnd.gen_range(0, size as u32) as usize;
                    swp_b0 = rnd.gen_range(0, (size + 1).min(n) as u32) as usize;
                    if swp_a0 == swp_b0 || (state[swp_a0].len() == 1 && swp_b0 == size) {
                        continue;
                    }
                    assert!(!state[swp_a0].is_empty());
                    swp_a1 = rnd.gen_range(0, state[swp_a0].len() as u32) as usize;
                    if swp_a1 != state[swp_a0].len() - 1 {
                        let l = state[swp_a0].len() - 1;
                        state[swp_a0].swap(swp_a1, l);
                    }
                    let v = state[swp_a0].pop().unwrap();
                    state[swp_b0].push(v);
                    break;
                }
            }
            let new_h0 = calc_needed_height(w, a, &state[swp_a0]);
            let new_h1 = calc_needed_height(w, a, &state[swp_b0]);
            let new_score = cur_score - cur_height[swp_a0] - cur_height[swp_b0] + new_h0 + new_h1;
            let ratio = (cur_time - timer_start) / (timer_end - timer_start);
            let rev_ratio = 1.0 - ratio;
            let temperature = initial_temp + (final_temp - initial_temp) * (1.0 - rev_ratio.pow(3));
            let delta = new_score as i32 - cur_score as i32;
            if delta < 0
                || (rnd.rand() as f64 / std::u32::MAX as f64)
                    < (-delta as f64 / temperature as f64).exp()
            {
                cur_score = new_score;
                cur_height[swp_a0] = new_h0;
                cur_height[swp_b0] = new_h1;
                if state[swp_a0].is_empty() {
                    let l = state_size[day] - 1;
                    state.swap(swp_a0, l);
                    cur_height.swap(swp_a0, l);
                    state_size[day] -= 1;
                }
                if swp_b0 == size {
                    state_size[day] += 1;
                }
                if best_score > cur_score {
                    best_score = cur_score;
                    best_states[day] = state.clone();
                }
            } else {
                if swp_b1 != !0 {
                    let v0 = state[swp_a0][swp_a1];
                    let v1 = state[swp_b0][swp_b1];
                    state[swp_a0][swp_a1] = v1;
                    state[swp_b0][swp_b1] = v0;
                } else {
                    let v = state[swp_b0].pop().unwrap();
                    state[swp_a0].push(v);
                }
            }
            cur_time = get_time();
        }
        eprintln!("Day {}: {}", day, best_score);
    }
    let mut prev_heights = gen_heights(&best_states[0], &r[0].0, w);
    let mut h_sum = prev_heights.iter().sum::<usize>();
    for i in h_sum..w {
        let l = prev_heights.len();
        prev_heights[rnd.gen_range(0, l as u32 - 1) as usize] += 1;
    }
    for (day, (a, count)) in r.iter().enumerate() {
        for _ in 0..*count {
            print_rectangle(&best_states[day], &prev_heights, a, w);
        }
        if day + 1 < r.len() {
            let mut cur_time = get_time();
            let timer_start = cur_time;
            let timer_end = (time_limit - cur_time) / (d - day - 1) as f64 + cur_time;
            let mut lined = vec![false; w];
            let mut cur_heights = gen_heights(&best_states[day + 1], &r[day + 1].0, w);
            let h_sum = cur_heights.iter().sum::<usize>();
            let mut h = 0;
            for v in prev_heights.iter() {
                h += *v;
                if h == lined.len() {
                    break;
                }
                lined[h] = true;
            }
            let (mut cur_score, mut cur_best_heights) =
                calc_best_heights(&lined, &cur_heights, h_sum);
            eprintln!("start: {}", cur_score);
            while cur_time < timer_end {
                let mut idx0 = 0;
                let mut idx1 = 0;
                while idx0 == idx1 {
                    idx0 = rnd.gen_range(0, cur_heights.len() as u32) as usize;
                    idx1 = rnd.gen_range(0, cur_heights.len() as u32) as usize;
                }
                cur_heights.swap(idx0, idx1);
                let (new_score, new_best_heights) = calc_best_heights(&lined, &cur_heights, h_sum);
                if new_score > cur_score {
                    best_states[day + 1].swap(idx0, idx1);
                    cur_best_heights = new_best_heights;
                    cur_score = new_score;
                } else {
                    cur_heights.swap(idx0, idx1);
                }
                cur_time = get_time();
            }
            eprintln!("end: {}", cur_score);
            prev_heights = cur_best_heights;
        }
    }

    // eprintln!("Best score: {}", best_score);
    eprintln!("Iteration count: {}", it_count);
}
