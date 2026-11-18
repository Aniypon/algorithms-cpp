#include <bits/stdc++.h>
using namespace std;

#define int long long

// Проверяет, содержит ли число нули
bool containsZero(int num) {
    string s = to_string(num);
    return s.find('0') != string::npos;
}

// Применяет операцию 1: увеличение первой цифры на 1
int operation1(int num) {
    string s = to_string(num);
    if (s[0] != '9') {
        s[0]++;
        return stoi(s);
    }
    return num;
}

// Применяет операцию 2: уменьшение последней цифры на 1
int operation2(int num) {
    string s = to_string(num);
    int len = s.length();
    if (s[len-1] != '1') {
        s[len-1]--;
        return stoi(s);
    }
    return num;
}

// Применяет операцию 3: циклический сдвиг вправо
int operation3(int num) {
    string s = to_string(num);
    char lastDigit = s[s.length()-1];
    s = lastDigit + s.substr(0, s.length()-1);
    return stoi(s);
}

// Применяет операцию 4: циклический сдвиг влево
int operation4(int num) {
    string s = to_string(num);
    char firstDigit = s[0];
    s = s.substr(1) + firstDigit;
    return stoi(s);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int start, target;
    cin >> start >> target;

    // BFS для поиска кратчайшего пути
    queue<int> q;
    map<int, int> parent;  // для восстановления пути
    map<int, bool> visited;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == target)
            break;

        // Применяем все возможные операции
        vector<int> next_states;
        next_states.push_back(operation1(current));
        next_states.push_back(operation2(current));
        next_states.push_back(operation3(current));
        next_states.push_back(operation4(current));

        for (int next : next_states) {
            if (!visited[next] && !containsZero(next)) {
                visited[next] = true;
                parent[next] = current;
                q.push(next);
            }
        }
    }

    // Восстановление пути
    vector<int> path;
    int current = target;
    while (current != start) {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(start);

    // Вывод пути в обратном порядке
    reverse(path.begin(), path.end());
    for (int num : path) {
        cout << num << endl;
    }

    return 0;
}