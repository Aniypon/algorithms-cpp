#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // Для каждого кружка будем хранить список кружков, которые зависят от него.
    vector<vector<int>> adj(N + 1);
    // Массив входящих степеней.
    vector<int> indegree(N + 1, 0);

    // Чтение описаний. Кружки нумеруются от 1 до N.
    for (int i = 1; i <= N; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int pre;
            cin >> pre;
            // Кружок pre должен быть посещён перед i-м кружком.
            // То есть существует ребро pre -> i.
            adj[pre].push_back(i);
            indegree[i]++;
        }
    }

    // Приоритетная очередь (min-heap) для кружков с indegree = 0.
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> order;
    order.reserve(N);

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        order.push_back(u);
        // Обновляем входящие степени всех, для которых u является предшественником.
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                pq.push(v);
            }
        }
    }

    // Вывод результата без завершающего пробела.
    for (size_t i = 0; i < order.size(); i++) {
        cout << order[i] << (i + 1 == order.size() ? "\n" : " ");
    }
    return 0;
}