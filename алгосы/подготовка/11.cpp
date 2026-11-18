#include <bits/stdc++.h>
using namespace std;

// Проверка, является ли строка периодической с заданным периодом
bool is_periodic(const string& s, int period) {
    int n = s.length();
    for (int i = period; i < n; i++) {
        if (s[i] != s[i % period]) {
            return false;
        }
    }
    return true;
}

int main() {
    // Ввод строки
    string s;
    cin >> s;

    int n = s.length();

    // Перебираем все возможные длины периода
    for (int period = 1; period <= n; period++) {
        if (is_periodic(s, period)) {
            // Нашли минимальный период
            cout << period << endl;
            return 0;
        }
    }

    // Если не нашли периода, длина S равна длине всей строки
    cout << n << endl;

    return 0;
}