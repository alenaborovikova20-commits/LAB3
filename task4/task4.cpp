#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

pair<long long, int> make_move(const vector<long long>& prefix, int current_pos, 
                                int m, int remaining, int early) {
    int max_count = min(m, remaining);
    
    int best_count = 0;
    long long best_sum = LLONG_MIN;
     for (int i = 1; i <= max_count; i++) {
        // нельзя повторять своё предыдущее количество
        if (i == early) continue;
        
        int end = current_pos + i;
        long long current_sum = prefix[end] - prefix[current_pos];
        
        // выбираем максимальную сумму, при равенстве - меньшее количество
        if (current_sum > best_sum || (current_sum == best_sum && i < best_count)) {
            best_sum = current_sum;
            best_count = i;
        }
    }
    
    
    return {best_sum, best_count};
}

int main() {
    int n, m;
    cout << "Введите зачение n: ";
    cin >> n;
    cout << "Введите значение m: ";
    cin  >> m;
    
    cout << "Введите последовательность чисел: ";
    vector<long long> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    

    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    

    long long pavel_score = 0;
    long long vika_score = 0;
    
    int current_pos = 0; 
    
    int pavel_early = 0;  
    int vika_early = 0;  
    
    bool turn = true;  // true - ход Павла false - ход Вики
    
    // Основной цикл игры
    while (current_pos < n) {
        int remaining = n - current_pos;
        
        auto [best_sum, best_count] = make_move(prefix, current_pos, m, remaining,  turn ? pavel_early : vika_early);
        
        // Применяем ход текущего игрока
        if (turn) {
            pavel_score += best_sum;
            pavel_early = best_count;
        } else {
            vika_score += best_sum;
            vika_early = best_count;
        }
        
        current_pos += best_count;
        turn = !turn;  // передаём ход другому игроку
    }
    
    cout << (pavel_score > vika_score ? 1 : 0) << endl;
    
    return 0;
}

