use std::io::Read;
use std::collections::VecDeque;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).ok();
    let mut iter = buf.split_whitespace();
    let t = iter.next().unwrap().parse::<usize>().unwrap();
    for case_id in 1..=t {
        let n = iter.next().unwrap().parse::<usize>().unwrap();
        let c = iter.next().unwrap().as_bytes();
        let mut st = VecDeque::new();
        for &s in c {
            if st.is_empty() || *st.back().unwrap() == s { st.push_back(s); }
            else { st.pop_back(); }
        }
        println!("Case #{}: {}", case_id, if st.len() == 1 { "Y" } else { "N" });
    }
}
