use std::io::{self, BufRead, Write};

fn make_move(prefix: &[i64], current_pos: usize, m: usize, remaining: usize, early: usize) -> (i64, usize) {
    let max_count = std::cmp::min(m, remaining);
    let mut best_sum = i64::MIN;
    let mut best_count = 0;

    for i in 1..=max_count {
        if i == early {
            continue;
        }
        let end = current_pos + i;
        let current_sum = prefix[end] - prefix[current_pos];
        if current_sum > best_sum || (current_sum == best_sum && i < best_count) {
            best_sum = current_sum;
            best_count = i;
        }
    }
    (best_sum, best_count)
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let mut stdout = io::stdout();

    print!("Введите значение n: ");
    stdout.flush().unwrap();
    let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();

    print!("Введите значение m: ");
    stdout.flush().unwrap();
    let m: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();

    print!("Введите последовательность чисел: ");
    stdout.flush().unwrap();
    let nums_line = lines.next().unwrap().unwrap();
    let nums: Vec<i64> = nums_line
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    assert_eq!(nums.len(), n);

    // Префиксные суммы
    let mut prefix = vec![0; n + 1];
    for i in 0..n {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    let mut pavel_score = 0;
    let mut vika_score = 0;
    let mut current_pos = 0;
    let mut pavel_early = 0;
    let mut vika_early = 0;
    let mut turn = true; // true - Павел, false - Вика

    while current_pos < n {
        let remaining = n - current_pos;
        let (best_sum, best_count) = make_move(
            &prefix,
            current_pos,
            m,
            remaining,
            if turn { pavel_early } else { vika_early },
        );

        if turn {
            pavel_score += best_sum;
            pavel_early = best_count;
        } else {
            vika_score += best_sum;
            vika_early = best_count;
        }

        current_pos += best_count;
        turn = !turn;
    }

    println!("{}", if pavel_score > vika_score { 1 } else { 0 });}

