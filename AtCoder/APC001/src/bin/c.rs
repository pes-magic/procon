use proconio::input;
use proconio::source::line::LineSource;

fn query<R: std::io::BufRead>(pos: usize, source: &mut LineSource<R>) -> i32 {
    println!("{}", pos);
    input! { from source, s: String }
    match s.chars().nth(0).unwrap() {
        'M' => 0,
        'F' => 1,
        _ => 2,
    }
}

fn main() {
    let stdin = std::io::stdin();
    let mut source = LineSource::new(std::io::BufReader::new(stdin.lock()));
    input! { from &mut source, n:usize }
    let mut result = vec![-1; n + 1];
    let mut low = 0;
    let mut high = n;
    result[0] = query(0, &mut source);
    result[n] = result[0];
    if result[0] == 2 {
        return;
    }
    loop {
        let mid = (low + high) / 2;
        result[mid] = query(mid, &mut source);
        if result[mid] == 2 {
            break;
        }
        if (mid - low) % 2 == 0 {
            if result[low] == result[mid] {
                low = mid;
            } else {
                high = mid;
            }
        } else {
            if result[low] != result[mid] {
                low = mid;
            } else {
                high = mid;
            }
        }
    }
}
