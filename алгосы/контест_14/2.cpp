#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    int key;
    int left;
    int right;
};

bool isBSTUtil(const vector<Node>& tree, int nodeIndex, int minKey, int maxKey) {
    if (nodeIndex == -1)
        return true;

    if (tree[nodeIndex].key <= minKey || tree[nodeIndex].key >= maxKey) {
        return false;
    }

    return isBSTUtil(tree, tree[nodeIndex].left, minKey, tree[nodeIndex].key) &&
           isBSTUtil(tree, tree[nodeIndex].right, tree[nodeIndex].key, maxKey);
}

bool isBST(const vector<Node>& tree) {
    if (tree.empty())
        return true;
    return isBSTUtil(tree, 0, LLONG_MIN, LLONG_MAX);
}

int32_t main() {
    int n;
    cin >> n;

    vector<Node> tree(n);

    for (int i = 0; i < n; ++i) {
        cin >> tree[i].key >> tree[i].left >> tree[i].right;
    }

    if (isBST(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }

    return 0;
}