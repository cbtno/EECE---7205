#include <iostream>
#include <utility>
using namespace std;

// PROBLEM 1 Bubble Sort
 
// Function 1: prints the n elements of arr on one line.
// Separated by spaces.
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << arr[i];
    }
}
 
// Function 2: sorts arr in increasing order using Bubble Sort algorithm.
// Counters are passed by reference so main() function can print the totals.
void bubbleSort(int arr[], int n, int &comparisons, int &swaps, int &passes) {
    comparisons = 0;
    swaps = 0;
    passes = 0;
 
    for (int pass = 0; pass < n - 1; pass++) {
        bool swapped = false;
 
        // After each pass the largest remaining element moves to end.
        // Unsorted part shrinks by one each pass.
        for (int j = 0; j < n - 1 - pass; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
                swapped = true;
            }
        }
 
        passes++;
        cout << "Pass " << passes << ": ";
        printArray(arr, n);
        cout << endl;
 
        if (!swapped) break;   // no swaps in this pass bc the array is sorted
    }
}
 
int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons, swaps, passes;
 
    // Run 1: original array A
    cout << "=== Run 1: original array A ===" << endl;
    cout << "Original: ";
    printArray(A, n);
    cout << endl;
 
    bubbleSort(A, n, comparisons, swaps, passes);
 
    cout << "Sorted: ";
    printArray(A, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << " Swaps: " << swaps << endl;
    cout << "Passes: " << passes << endl << endl;
 
    // ---- Run 2:sorted copy A ----
    int S[] = {5, 7, 14, 19, 23, 32, 34, 62};
    cout << "=== Run 2: already sorted copy of A ===" << endl;
    cout << "Original: ";
    printArray(S, n);
    cout << endl;
 
    bubbleSort(S, n, comparisons, swaps, passes);
 
    cout << "Sorted: ";
    printArray(S, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << " Swaps: " << swaps << endl;
    cout << "Passes: " << passes << endl;
 
    return 0;
}
 