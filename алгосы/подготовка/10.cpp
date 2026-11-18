#include <iostream>
#include <vector>

using namespace std;

// Функция для перестановки двух элементов
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Реализация алгоритма быстрой сортировки (средний элемент как опорный)
void quicksort(vector<int> &arr, int start, int end) {
    // Если в рабочей части массива меньше двух элементов, выходим
    if (start >= end) {
        return;
    }

    // Выбираем средний элемент как опорный
    int pivotIndex = start + (end - start) / 2;
    int pivot = arr[pivotIndex];

    // Указатели для разделения массива
    int left = start, right = end;

    while (left <= right) {
        // Ищем элементы для перестановки
        while (arr[left] < pivot) {
            left++;
        }
        while (arr[right] > pivot) {
            right--;
        }

        // Если нужно, делаем перестановку
        if (left <= right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    // Рекурсивно сортируем левую и правую части
    quicksort(arr, start, right);
    quicksort(arr, left, end);
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quicksort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}