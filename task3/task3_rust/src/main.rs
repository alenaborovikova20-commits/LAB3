use num_integer::Integer;
use std::io;

// Функция коэффициентов Эйлера 
fn euler_coeff(a: usize) -> Vec<i64> {
    let mut vec = vec![vec![]; a + 1];
    for n in 1..=a {
        vec[n].resize(n, 0);
        vec[n][0] = 1;
        for j in 1..n {
            let first = ((n - j) as i64) * vec[n - 1][j - 1];
            let second = if j < n - 1 {
                ((j + 1) as i64) * vec[n - 1][j]
            } else {
                0
            };
            vec[n][j] = first + second;
        }
        if n > 1 {
            vec[n][n - 1] = 1;
        }
    }
    vec[a].clone()
}


fn rational_sum(a: usize, b: i64) -> (i64, i64) {
    let euler = euler_coeff(a);
    let mut numerator = 0i64;
    for k in 0..a {
        let exp = (a - k) as u32;
        let pow_b = b.pow(exp); // b^{a-k}
        numerator += euler[k] * pow_b;
    }
    let mut denominator = 1i64;
    for _ in 0..=a {
        denominator *= b - 1;
    }
    let g = numerator.gcd(&denominator);
    (numerator / g, denominator / g)
}

fn main() {
    loop {
        println!("Введите число a:");
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Ошибка чтения");
        let a: usize = input.trim().parse().expect("Введите целое число от 1 до 10");

        println!("Введите число b:");
        input.clear();
        io::stdin().read_line(&mut input).expect("Ошибка чтения");
        let b: i64 = input.trim().parse().expect("Введите целое число");

        if b <= 1 {
            println!("infinity");
        } else {
            let (num, den) = rational_sum(a, b);
            println!("{}/{}", num, den);
        }
        break;
    }
}

