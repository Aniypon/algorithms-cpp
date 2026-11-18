#include <bits/stdc++.h>
using namespace std;

#define int long long

// Функция для подсчета числа палиндромных подстрок
int countPalindromes(const string& s) {
    int n = s.length();
    int count = 0;
    
    // Проверяем палиндромы нечетной длины (включая односимвольные)
    for (int i = 0; i < n; i++) {
        int left = i, right = i;
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    }
    
    // Проверяем палиндромы четной длины
    for (int i = 0; i < n - 1; i++) {
        int left = i, right = i + 1;
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    }
    
    return count;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    
    // Вычитаем длину строки, чтобы не учитывать односимвольные палиндромы.
    cout << countPalindromes(s) - s.size() << "\n";
    
    return 0;
}