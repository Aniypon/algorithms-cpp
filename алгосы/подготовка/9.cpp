#include <bits/stdc++.h>
using namespace std;

#define int long long

// Функция для перестройки поддерева с корнем i, чтобы оно удовлетворяло свойствам кучи
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;        // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1;   // Левый потомок
    int right = 2 * i + 2;  // Правый потомок

    // Если левый потомок существует и больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый потомок существует и больше наибольшего на данный момент
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если наибольший элемент не корень
    if (largest != i) {
        swap(arr[i], arr[largest]);
        // Рекурсивно перестраиваем затронутое поддерево
        heapify(arr, n, largest);
    }
}

// Функция пирамидальной сортировки
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Строим максимальную кучу (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Извлекаем элементы из кучи по одному
    for (int i = n - 1; i > 0; i--) {
        // Перемещаем текущий корень (максимальный элемент) в конец
        swap(arr[0], arr[i]);

        // Вызываем heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    heapSort(arr);

    // Вывод отсортированного массива
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}