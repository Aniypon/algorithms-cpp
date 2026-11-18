#include <bits/stdc++.h>
using namespace std;

#define int long long

struct FlowEdge {
    int dest, capacity, flow, backEdge;
};

class MaxFlow {
   private:
    int nodes;
    vector<vector<FlowEdge>> graph;
    vector<int> dist, edgePointer;

    bool buildLevelGraph(int src, int sink) {
        dist.assign(nodes, -1);
        dist[src] = 0;

        queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const auto& e : graph[u]) {
                if (dist[e.dest] == -1 && e.flow < e.capacity) {
                    dist[e.dest] = dist[u] + 1;
                    q.push(e.dest);
                }
            }
        }

        return dist[sink] != -1;
    }

    int pushFlow(int u, int sink, int minCapacity) {
        if (u == sink)
            return minCapacity;

        for (; edgePointer[u] < graph[u].size(); edgePointer[u]++) {
            FlowEdge& edge = graph[u][edgePointer[u]];

            if (dist[edge.dest] == dist[u] + 1 && edge.flow < edge.capacity) {
                int pushed = pushFlow(edge.dest, sink, min(minCapacity, edge.capacity - edge.flow));

                if (pushed > 0) {
                    edge.flow += pushed;
                    graph[edge.dest][edge.backEdge].flow -= pushed;
                    return pushed;
                }
            }
        }

        return 0;
    }

   public:
    MaxFlow(int n) : nodes(n) {
        graph.resize(n);
        dist.resize(n);
        edgePointer.resize(n);
    }

    void addConnection(int from, int to, int capacity) {
        FlowEdge forward = {to, capacity, 0, (int)graph[to].size()};
        FlowEdge reverse = {from, 0, 0, (int)graph[from].size()};

        graph[from].push_back(forward);
        graph[to].push_back(reverse);
    }

    int calculateMaxFlow(int src, int sink) {
        int maxFlow = 0;

        while (buildLevelGraph(src, sink)) {
            edgePointer.assign(nodes, 0);

            while (int flow = pushFlow(src, sink, LLONG_MAX)) {
                maxFlow += flow;
            }
        }

        return maxFlow;
    }

    vector<vector<FlowEdge>>& getGraph() {
        return graph;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<pair<char, char>> cards(n + 1);
    for (int i = 1; i <= n; i++) {
        string card;
        cin >> card;
        cards[i] = {card[0], card[1]};
    }

    string targetWord;
    cin >> targetWord;
    int wordLength = targetWord.size();

    if (wordLength > n) {
        cout << "IMPOSSIBLE";
        return;
    }

    vector<int> letterCount(26, 0);
    for (char c : targetWord) {
        letterCount[c - 'a']++;
    }

    int totalNodes = 26 + n + 2;
    int source = 0, sink = totalNodes - 1;
    MaxFlow flowNetwork(totalNodes);

    for (int letter = 0; letter < 26; letter++) {
        if (letterCount[letter] > 0) {
            flowNetwork.addConnection(source, 1 + letter, letterCount[letter]);
        }
    }

    for (int cardIdx = 1; cardIdx <= n; cardIdx++) {
        char firstLetter = cards[cardIdx].first;
        char secondLetter = cards[cardIdx].second;

        if (firstLetter == secondLetter) {
            int letterNode = 1 + (firstLetter - 'a');
            flowNetwork.addConnection(letterNode, 26 + cardIdx, 1);
        } else {
            flowNetwork.addConnection(1 + (firstLetter - 'a'), 26 + cardIdx, 1);
            flowNetwork.addConnection(1 + (secondLetter - 'a'), 26 + cardIdx, 1);
        }

        flowNetwork.addConnection(26 + cardIdx, sink, 1);
    }

    int maxFlow = flowNetwork.calculateMaxFlow(source, sink);
    if (maxFlow != wordLength) {
        cout << "IMPOSSIBLE";
        return;
    }

    vector<char> assignedLetters(n + 1, 0);
    auto& graph = flowNetwork.getGraph();

    for (int letterNode = 1; letterNode <= 26; letterNode++) {
        for (const auto& edge : graph[letterNode]) {
            if (edge.dest >= 27 && edge.dest <= 26 + n && edge.flow > 0) {
                int cardIdx = edge.dest - 26;
                assignedLetters[cardIdx] = 'a' + (letterNode - 1);
            }
        }
    }

    vector<vector<int>> letterToCards(26);
    for (int idx = 1; idx <= n; idx++) {
        if (assignedLetters[idx] != 0) {
            letterToCards[assignedLetters[idx] - 'a'].push_back(idx);
        }
    }

    vector<int> result(wordLength);
    vector<int> usedCardCount(26, 0);

    for (int i = 0; i < wordLength; i++) {
        int letterIdx = targetWord[i] - 'a';
        int cardIdx = letterToCards[letterIdx][usedCardCount[letterIdx]++];

        if (cards[cardIdx].first == targetWord[i]) {
            result[i] = cardIdx;
        } else {
            result[i] = -cardIdx;
        }
    }

    for (int i = 0; i < wordLength; i++) {
        cout << result[i] << " ";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases = 1;

    while (testCases--) {
        solve();
    }

    return 0;
}