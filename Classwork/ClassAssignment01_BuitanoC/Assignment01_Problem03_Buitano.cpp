#include <iostream>
#include <utility>
using namespace std;
 
// PROBLEM 3 Selection Sort

// Function 1: prints the n elements of array on one line.
// Separated by spaces.
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << arr[i];
    }
}
 
// Function 2: sorts array in increasing order using Selection Sort.
void selectionSort(int arr[], int n, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;
 
    for (int i = 0; i < n - 1; i++) {
        // Find the smallest element in the unsorted part of array.
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
 
        cout << "Pass " << (i + 1) << ": min = " << arr[minIdx]
             << " at index " << minIdx << " -> ";
 
        // Here it swaps only if the minimum is not already in position.
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            swaps++;
        }
 
        printArray(arr, n);
        cout << endl;
    }
}
 
int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons, swaps;
 
    cout << "Original: ";
    printArray(A, n);
    cout << endl;
 
    selectionSort(A, n, comparisons, swaps);
 
    cout << "Sorted: ";
    printArray(A, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << " Swaps: " << swaps << endl;
 
    return 0;
}
