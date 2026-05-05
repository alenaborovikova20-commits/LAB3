#include <iostream>
#include <vector>
#include <cmath>
#include <numeric> // для gcd

using namespace std;

// Функция коэффициентов Эйлера
vector<int> eulerCoeff(int a) {
    vector<vector<int>> vec(a + 1);
    for (int n = 1; n <= a; n++) {
        vec[n].resize(n);
        vec[n][0] = 1;
        for (int j = 1; j < n; j++) {
            
            int second = (j + 1) * ((j < n-1) ? vec[n-1][j] : 0);
            vec[n][j] = (n - j) * vec[n-1][j-1] + second;
        }
        if (n > 1) vec[n][n-1] = 1;
    }
    return vec[a];
}



pair<long long, long long> rationalSum(int a, int b) {
    vector<int> euler = eulerCoeff(a);
    
    // Вычисляем числитель
    long long numerator = 0, pow_b = 0;
    for (int k = 0; k < a; ++k) {
        pow_b = pow(b, a - k);
        numerator += (long long)euler[k] * pow_b;
    }
    
    // Вычисляем знаменатель
    long long denominator = 1;
    for (int p = 0; p < a + 1; ++p) {
        denominator *= (b - 1);
    }
    
    //Сокращаем дробь на НОД
    long long g = gcd(numerator, denominator);  
    numerator /= g;   
    denominator /= g; 
    
    return {numerator, denominator};
}

int main() {
    while (true) {
        cout << "Введите число a: " << endl;
        int a;
        cin >> a;
        cout << "Введите число b: " << endl;
        int b;
        cin >> b;
        if (b <= 1) {
            cout << "infinity" << endl;
        } else {
            auto [num, den] = rationalSum(a, b);
            cout << num << "/" << den << endl;
        }
        break;
    }
    return 0;
}

