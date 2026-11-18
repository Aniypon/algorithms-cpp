#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    int key;
    int left;
    int right;
};

void inOrder(const vector<Node>& tree, int node, vector<int>& result) {
    if (node == -1)
        return;
    inOrder(tree, tree[node].left, result);
    result.push_back(tree[node].key);
    inOrder(tree, tree[node].right, result);
}

void preOrder(const vector<Node>& tree, int node, vector<int>& result) {
    if (node == -1)
        return;
    result.push_back(tree[node].key);
    preOrder(tree, tree[node].left, result);
    preOrder(tree, tree[node].right, result);
}

void postOrder(const vector<Node>& tree, int node, vector<int>& result) {
    if (node == -1)
        return;
    postOrder(tree, tree[node].left, result);
    postOrder(tree, tree[node].right, result);
    result.push_back(tree[node].key);
}

int32_t main() {
    int n;
    cin >> n;
    vector<Node> tree(n);

    for (int i = 0; i < n; i++) {
        cin >> tree[i].key >> tree[i].left >> tree[i].right;
    }

    vector<int> inOrderResult, preOrderResult, postOrderResult;

    inOrder(tree, 0, inOrderResult);
    preOrder(tree, 0, preOrderResult);
    postOrder(tree, 0, postOrderResult);

    // Вывод результатов
    for (size_t i = 0; i < inOrderResult.size(); i++) {
        cout << inOrderResult[i];
        if (i < inOrderResult.size() - 1)
            cout << " ";
    }
    cout << endl;

    for (size_t i = 0; i < preOrderResult.size(); i++) {
        cout << preOrderResult[i];
        if (i < preOrderResult.size() - 1)
            cout << " ";
    }
    cout << endl;

    for (size_t i = 0; i < postOrderResult.size(); i++) {
        cout << postOrderResult[i];
        if (i < postOrderResult.size() - 1)
            cout << " ";
    }
    cout << endl;

    return 0;
}