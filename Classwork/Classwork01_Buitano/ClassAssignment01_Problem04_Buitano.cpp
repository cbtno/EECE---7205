#include <iostream>
#include <utility>
using namespace std;
 
// PROBLEM 4 Quick Sort

// Function 1: prints the n elements of arr on one line.
// Separated by spaces.
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << arr[i];
    }
}
 
int partition(int arr[], int low, int high, int &comparisons, bool trace) {
    int pivot = arr[high];
    int i = low - 1;           
 
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            if (trace) {
                cout << "      swap i = " << i << ", j = " << j << ": ";
                printArray(arr + low, high - low + 1);
                cout << endl;
            }
        }
    }
 
    swap(arr[i + 1], arr[high]);
    if (trace) {
        cout << "      pivot swap (index " << i + 1 << " <-> " << high << "): ";
        printArray(arr + low, high - low + 1);
        cout << endl;
        cout << "      pivot " << pivot << " final position = index " << i + 1 << endl;
    }
    return i + 1;
}
 
// Function 2: sorts array from low to high in increasing order using Quick Sort algo.
void quickSort(int arr[], int low, int high, int &comparisons,
               int depth = 0, bool traceFirst = false) {
    if (low < high) {
        for (int d = 0; d < depth; d++) cout << "  ";   // indent = recursion tree
        cout << "pivot = " << arr[high] << ": ";
        printArray(arr + low, high - low + 1);
        cout << endl;
 
        int p = partition(arr, low, high, comparisons, traceFirst && depth == 0);
 
        quickSort(arr, low, p - 1, comparisons, depth + 1, false);
        quickSort(arr, p + 1, high, comparisons, depth + 1, false);
    }
}
 
int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0;
 
    // Run 1: the original array A 
    cout << "=== Run 1: original array A ===" << endl;
    cout << "Original: ";
    printArray(A, n);
    cout << endl;
 
    quickSort(A, 0, n - 1, comparisons, 0, true);
 
    cout << "Sorted: ";
    printArray(A, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << endl << endl;
 
    // Run 2: already sorted copy of A 
    int S[] = {5, 7, 14, 19, 23, 32, 34, 62};
    comparisons = 0;
    cout << "=== Run 2: already sorted copy of A ===" << endl;
    cout << "Original: ";
    printArray(S, n);
    cout << endl;
 
    quickSort(S, 0, n - 1, comparisons);
 
    cout << "Sorted: ";
    printArray(S, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << endl;
 
    return 0;
}
 