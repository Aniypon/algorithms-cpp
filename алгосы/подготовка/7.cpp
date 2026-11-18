#include <iostream>

using namespace std;

long long findCx(int x) {
    int count = 0; // счетчик найденных элементов последовательности C
    int idxA = 1, idxB = 1; // индексы для последовательностей A и B
    
    while (true) {
        long long elemA = (long long)idxA * idxA;        // i-й элемент последовательности A
        long long elemB = (long long)idxB * idxB * idxB; // i-й элемент последовательности B
        
        if (elemA < elemB) {
            // Если текущий элемент A меньше текущего элемента B,
            // добавляем A в последовательность C
            count++;
            if (count == x) return elemA;
            idxA++;
        } else if (elemB < elemA) {
            // Если текущий элемент B меньше текущего элемента A,
            // добавляем B в последовательность C
            count++;
            if (count == x) return elemB;
            idxB++;
        } else { // elemA == elemB
            // Если элементы равны, добавляем только один из них
            // и продвигаем оба указателя
            count++;
            if (count == x) return elemA;
            idxA++;
            idxB++;
        }
    }
}

int main() {
    int x;
    cin >> x;
    cout << findCx(x) << endl;
    return 0;
}