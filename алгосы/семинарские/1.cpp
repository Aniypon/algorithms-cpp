#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> timeProd(n+1);
    for (int i = 1; i <= n; i++){
        cin >> timeProd[i];
    }
    
    // prereq[i] содержит детали, которые необходимо произвести до детали i
    vector<vector<int>> prereq(n+1);
    for (int i = 1; i <= n; i++){
        int k;
        cin >> k;
        prereq[i].resize(k);
        for (int j = 0; j < k; j++){
            cin >> prereq[i][j];
        }
    }
    
    // Шаг 1: определить множество деталей, необходимых для производства детали 1
    vector<bool> needed(n+1, false);
    // используем стек для обхода в глубину
    stack<int> st;
    st.push(1);
    while(!st.empty()){
        int cur = st.top();
        st.pop();
        if(needed[cur]) continue;
        needed[cur] = true;
        for(auto pre : prereq[cur]){
            if(!needed[pre]){
                st.push(pre);
            }
        }
    }
    
    // Шаг 2: суммарное время и подсчёт деталей
    int totalTime = 0, countNeeded = 0;
    for (int i = 1; i <= n; i++){
        if(needed[i]){
            totalTime += timeProd[i];
            countNeeded++;
        }
    }
    
    // Шаг 3: построение зависимостей для топологической сортировки.
    // Нам нужен граф, где ребра: pre -> i, если i требует pre.
    vector<vector<int>> graph(n+1);
    vector<int> inDegree(n+1, 0);
    for (int i = 1; i <= n; i++){
        if(!needed[i]) continue;
        for(auto pre : prereq[i]){
            if(needed[pre]){
                graph[pre].push_back(i);
                inDegree[i]++;
            }
        }
    }
    
    // Шаг 4: топологическая сортировка (Кан)
    queue<int> q;
    // выбираем детали, которые можно сразу произвести (без предварительного производства)
    for (int i = 1; i <= n; i++){
        if(needed[i] && inDegree[i] == 0){
            q.push(i);
        }
    }
    
    vector<int> productionOrder;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        productionOrder.push_back(cur);
        for(auto nxt : graph[cur]){
            inDegree[nxt]--;
            if(inDegree[nxt] == 0)
                q.push(nxt);
        }
    }
    
    // В топологической сортировке деталь 1 обязательно должна идти позже всех своих предшественников.
    // Если требуется именно, чтобы деталь 1 была последней, можно перестроить последовательность:
    // Найдём позицию детали 1 и переместим её в конец, сохранив относительный порядок остальных.
    auto it = find(productionOrder.begin(), productionOrder.end(), 1);
    if(it != productionOrder.end()){
        int part1 = *it;
        productionOrder.erase(it);
        productionOrder.push_back(part1);
    }
    
    cout << totalTime << " " << countNeeded << "\n";
    for (auto part : productionOrder){
        cout << part << " ";
    }
    cout << "\n";
    
    return 0;
}