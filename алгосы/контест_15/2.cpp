#include <bits/stdc++.h>
using namespace std;

#define int long long

long double area(long double x1, long double y1, long double x2, long double y2, long double x3, long double y3) {
    return abs(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2));
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int ax, ay, bx, by, cx, cy, px, py;
    cin >> ax >> ay >> bx >> by >> cx >> cy >> px >> py;
    
    long double A = area(ax, ay, bx, by, cx, cy);
    long double A1 = area(px, py, bx, by, cx, cy);
    long double A2 = area(ax, ay, px, py, cx, cy);
    long double A3 = area(ax, ay, bx, by, px, py);
    
    if (abs(A - (A1 + A2 + A3)) < 1e-9)
        cout << "In";
    else
        cout << "Out";
    
    return 0;
}