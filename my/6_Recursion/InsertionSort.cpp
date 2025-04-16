#include <iostream>
using namespace std;

void insertSorted(int arr[], int n) {
    int key = arr[n - 1];
    int j = n - 2;

    while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j]; 
        j--;
    }
    arr[j + 1] = key;
}

void recursiveInsertionSort(int arr[], int n) {
    if (n <= 1)
        return;

    recursiveInsertionSort(arr, n - 1);

    insertSorted(arr, n);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {5, 3, 1, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]); // 陣列總位元組大小 / 一個元素的大小

    cout << "原始陣列：";
    printArray(arr, n);

    recursiveInsertionSort(arr, n);

    cout << "排序後陣列：";
    printArray(arr, n);

    return 0;
}
