#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val, prior, sz;
    Node *l, *r;
    Node(int v) : val(v), prior(rand()), sz(1), l(nullptr), r(nullptr) {}
};

int sz(Node* t) { 
    return t ? t->sz : 0; 
}

void upd(Node* t) {
    if(t) {
        t->sz = 1 + sz(t->l) + sz(t->r);
    }
}

void split(Node* t, int key, Node*& l, Node*& r) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    int cur_key = sz(t->l) + 1;
    if (cur_key <= key) {
        split(t->r, key - cur_key, t->r, r);
        l = t;
    } else {
        split(t->l, key, l, t->l);
        r = t;
    }
    upd(t);
}

Node* merge(Node* l, Node* r) {
    if (!l || !r) return l ? l : r;
    if (l->prior > r->prior) {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}

void inorder(Node* t, vector<int>& res) {
    if (!t) return;
    inorder(t->l, res);
    res.push_back(t->val);
    inorder(t->r, res);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Node* root = nullptr;
    // Построение начального дерева: [1, 2, ..., n]
    for (int i = 1; i <= n; i++){
        root = merge(root, new Node(i));
    }
    
    while(m--){
        int l, r;
        cin >> l >> r;
        Node *A, *B, *C;
        // Разбиваем дерево на две части: первые l-1 элементов и остальные.
        split(root, l - 1, A, B);
        // Далее выделяем из B отрезок размера (r - l + 1).
        split(B, r - l + 1, B, C);
        // Теперь B – отрезок, который требуется перенести в начало.
        // Новый порядок: B, затем A, затем C.
        root = merge(B, merge(A, C));
    }
    
    vector<int> ans;
    inorder(root, ans);
    for(auto x : ans)
        cout << x << " ";
    cout << "\n";
    return 0;
}