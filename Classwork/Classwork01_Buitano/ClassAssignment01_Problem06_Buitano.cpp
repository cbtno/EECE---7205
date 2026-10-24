#include <iostream>
#include <utility>
using namespace std;
 
// PROBLEM 6 Heap Sort

// Function 1: prints the n elements of arr on one line, separated by spaces.
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << arr[i];
    }
}
 
// Restores the max-heap property for the subtree rooted at 'root',
// considering only the first 'size' elements. Counts swaps.
void siftDown(int arr[], int root, int size, int &swaps) {
    while (true) {
        int largest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;
 
        if (left < size && arr[left] > arr[largest])   largest = left;
        if (right < size && arr[right] > arr[largest]) largest = right;
 
        if (largest == root) break;       // parent >= both children: done
 
        swap(arr[root], arr[largest]);
        swaps++;
        root = largest;                   // continue sifting down
    }
}
 
// Function 2: sorts arr in increasing order using Heap Sort.
void heapSort(int arr[], int n, int &swaps) {
    swaps = 0;
 
    // Phase 1: build a max-heap (start from the last non-leaf node)
    for (int k = n / 2 - 1; k >= 0; k--) {
        siftDown(arr, k, n, swaps);
    }
    cout << "Heap: ";
    printArray(arr, n);
    cout << endl;
 
    // Phase 2: repeatedly move the max (root) to the end and re-heapify
    for (int end = n - 1; end >= 1; end--) {
        swap(arr[0], arr[end]);
        siftDown(arr, 0, end, swaps);
 
        cout << "end = " << end << ": heap: ";
        printArray(arr, end);
        cout << " sorted: ";
        printArray(arr + end, n - end);
        cout << endl;
    }
}
 
int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int swaps;
 
    cout << "Original: ";
    printArray(A, n);
    cout << endl;
 
    heapSort(A, n, swaps);
 
    cout << "Sorted: ";
    printArray(A, n);
    cout << endl;
    cout << "Swaps in siftDown: " << swaps << endl;
 
    return 0;
}
 