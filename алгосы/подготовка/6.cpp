#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> durability(n+1); // Прочность каждой клавиши (индексация с 1)
    for (int i = 1; i <= n; i++) {
        cin >> durability[i];
    }
    
    int k;
    cin >> k;
    
    vector<int> presses(n+1, 0); // Счетчик нажатий для каждой клавиши
    
    for (int j = 0; j < k; j++) {
        int key;
        cin >> key;
        presses[key]++;
    }
    
    // Определяем сломанные клавиши
    for (int i = 1; i <= n; i++) {
        // Клавиша сломана, если количество нажатий превысило её прочность
        cout << (presses[i] > durability[i] ? "yes" : "no") << endl;
    }
    
    return 0;
}