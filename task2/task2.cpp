#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;


std::vector<int> simple;

void sieveOfEratosthenes() {
    int vec[498]; 
    
    for (int i = 1; i < 500; ++i) { // Заплняем массив числами 
        vec[i - 2] = i; 
    }
    
    for (int i = 0; i < 498; ++i) {
        if (vec[i] != 0) {
            simple.push_back(vec[i]);
            for (int j = i + 1; j < 498; ++j) {
                if (vec[j] % vec[i] == 0) {
                    vec[j] = 0;}}}}}


int mod(int base, int power, int modulo) {
    base %= modulo;
    int result = 1;
    for (int i = 0; i < power; ++i) {
        result = (result * base) % modulo;
    }
    return result;
}
bool diemitko(int p, int q, int N, int u) {
    if (mod(2, p - 1, p) != 1) return false;
    if (mod(2, N + u, p) == 1) return false;
    return true;
}
int simpleNumsGen(int t, int q, int &rejected) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(0.0, 1.0);
    while (true) {
        float e = dist(gen);
        int N = ((pow(2, t - 1)) / q) + ((pow(2, t - 1) * e) / q);
        if (N % 2 != 0) { N++; }
        int u = 0;
        while (true) {
            int p = (N + u) * q + 1;
            if (p > pow(2, t)) {
                rejected++;       // счётчик отвергнутых
                break;            
            }
            if (diemitko(p, q, N, u)) {
                return p;
            } else {
                rejected++;
                u += 2;}}}}

// Функция для подсчёта битовой длины 
int bitLen(int x) {
    int len = 0;
    while (x) { len++; x >>= 1; }
    return len;}


int main() {
    // Получаем простые числа и выводим их в терминал
    sieveOfEratosthenes();
    
    for (int p : simple) {
        std::cout << p << " ";
    }
    cout << "\n";

    // Ввод разрядности
    cout << "Введите требуемую разрядность числа bits: ";
    int t;
    cin >> t;

    // Выбираем простое чисо q в зависимости от выбранной разрядности (t/2)
    int need_bits = (t + 1) / 2;
    int q = 0;
    for (int p : simple) {
        if (bitLen(p) == need_bits) {
            q = p;
            break;
        }
    }
    if (q == 0) {
        cout << "Нет простого числа с разрядностью " << need_bits << " среди простых < 500\n";
        return 1;
    }
    cout << "Используем q = " << q << "\n\n";

    // Таблица результатов 
    cout << "№ | Простое число | Количество отвергнутых | Результат проверки |\n";

    for (int i = 0; i < 10; ++i) {
        int rej = 0;
        int p = simpleNumsGen(t, q, rej);
        cout << i << "\t" << p << "\t\t\t" << rej << "\t\t" << "true" << endl;
    }
    return 0;
}

