#include <iostream>
#include <vector>
using namespace std;
 
// PROBLEM 5 Merge Sort

// Function 1: prints the n elements of arr on one line, separated by spaces.
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << arr[i];
    }
}
 
// Merges the sorted halves.
void merge(int arr[], int low, int mid, int high, int &comparisons) {
    vector<int> L(arr + low, arr + mid + 1);
    vector<int> R(arr + mid + 1, arr + high + 1);
 
    size_t i = 0, j = 0;
    int k = low;
 
    while (i < L.size() && j < R.size()) {
        comparisons++;
        if (L[i] <= R[j]) arr[k++] = L[i++];   
        else              arr[k++] = R[j++];
    }
    while (i < L.size()) arr[k++] = L[i++];    // leftovers do not need more comparisons
    while (j < R.size()) arr[k++] = R[j++];
}
 
// Function 2: sorts array in increasing order using Merge Sort algo.
// finalMerge receives the number of comparisons made in the top-level merge.
void mergeSort(int arr[], int low, int high, int &comparisons, int &finalMerge,
               bool verbose = true, int depth = 0) {
    if (low >= high) return;   
 
    if (verbose) {
        cout << "split: ";
        printArray(arr + low, high - low + 1);
        cout << endl;
    }
 
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid, comparisons, finalMerge, verbose, depth + 1);
    mergeSort(arr, mid + 1, high, comparisons, finalMerge, verbose, depth + 1);
 
    int before = comparisons;
    merge(arr, low, mid, high, comparisons);
    if (depth == 0) finalMerge = comparisons - before;
 
    if (verbose) {
        cout << "merged: ";
        printArray(arr + low, high - low + 1);
        cout << endl;
    }
}
 
int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons, finalMerge;
 
    // Run 1: original array A 
    comparisons = 0; finalMerge = 0;
    cout << "=== Run 1: original array A ===" << endl;
    cout << "Original: ";
    printArray(A, n);
    cout << endl;
    mergeSort(A, 0, n - 1, comparisons, finalMerge, true);
    cout << "Sorted: ";
    printArray(A, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << " (final merge: " << finalMerge << ")" << endl << endl;
 
    // Run 2: sorted copy of A 
    int S[] = {5, 7, 14, 19, 23, 32, 34, 62};
    comparisons = 0; finalMerge = 0;
    cout << "=== Run 2: sorted copy of A ===" << endl;
    cout << "Original: ";
    printArray(S, n);
    cout << endl;
    mergeSort(S, 0, n - 1, comparisons, finalMerge, false);
    cout << "Sorted: ";
    printArray(S, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << " (final merge: " << finalMerge << ")" << endl << endl;
 
    // Run 3: reversed copy of A aka decreasing
    int R[] = {62, 34, 32, 23, 19, 14, 7, 5};
    comparisons = 0; finalMerge = 0;
    cout << "=== Run 3: reversed (decreasing) copy of A ===" << endl;
    cout << "Original: ";
    printArray(R, n);
    cout << endl;
    mergeSort(R, 0, n - 1, comparisons, finalMerge, false);
    cout << "Sorted: ";
    printArray(R, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << " (final merge: " << finalMerge << ")" << endl;
 
    return 0;
}
 