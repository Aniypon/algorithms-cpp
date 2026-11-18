#include <bits/stdc++.h>
using namespace std;

#define int long long

// Возможные ходы коня
const int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    
    // Если конь уже находится в целевой клетке
    if (x1 == x2 && y1 == y2) {
        cout << 0 << endl;
        cout << x1 << " " << y1 << endl;
        return 0;
    }
    
    // Массив для хранения предыдущей позиции для каждой клетки
    vector<vector<pair<int, int>>> prev(n + 1, vector<pair<int, int>>(n + 1, {-1, -1}));
    // Расстояние до каждой клетки
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
    
    queue<pair<int, int>> q;
    q.push({x1, y1});
    dist[x1][y1] = 0;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        if (x == x2 && y == y2) {
            break; // Нашли целевую клетку
        }
        
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                prev[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }
    
    // Восстанавливаем путь
    vector<pair<int, int>> path;
    int currX = x2, currY = y2;
    while (currX != -1 && currY != -1) {
        path.push_back({currX, currY});
        auto [prevX, prevY] = prev[currX][currY];
        currX = prevX;
        currY = prevY;
    }
    
    reverse(path.begin(), path.end());
    
    // Выводим результат
    cout << dist[x2][y2] << endl;
    for (auto [x, y] : path) {
        cout << x << " " << y << endl;
    }
    
    return 0;
}