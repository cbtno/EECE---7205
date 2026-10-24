#include <iostream>
using namespace std;

// PROBLEM 2 Insertion Sort

// Function 1: prints the n elements of arr on one line, separated by spaces.
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << arr[i];
    }
}
 
// Function 2: sorts arr in increasing order using Insertion Sort.
void insertionSort(int arr[], int n, int &comparisons, int &shifts) {
    comparisons = 0;
    shifts = 0;
 
    for (int i = 1; i < n; i++) {
        int key = arr[i];     // next element to insert into the sorted part
        int j = i - 1;
 
        // Move every element of the sorted part that is larger than key
        // one position to the right.
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                shifts++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;     // drop key into the gap
 
        cout << "i = " << i << ", key = " << key << ": ";
        printArray(arr, n);
        cout << endl;
    }
}
 
int main() {
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons, shifts;
 
    // Run 1: the original array A 
    cout << "Run 1: original array A" << endl;
    cout << "Original: ";
    printArray(A, n);
    cout << endl;
    insertionSort(A, n, comparisons, shifts);
    cout << "Sorted: ";
    printArray(A, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << " Shifts: " << shifts << endl << endl;
 
    // Run 2: increasing order so fewest shifts & best case
    int best[] = {5, 7, 14, 19, 23, 32, 34, 62};
    cout << "Run 2: increasing order (fewest shifts)" << endl;
    cout << "Original: ";
    printArray(best, n);
    cout << endl;
    insertionSort(best, n, comparisons, shifts);
    cout << "Sorted: ";
    printArray(best, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << " Shifts: " << shifts << endl << endl;
 
    // Run 3: decreasing order so most shifts & worst case
    int worst[] = {62, 34, 32, 23, 19, 14, 7, 5};
    cout << "Run 3: decreasing order (most shifts)" << endl;
    cout << "Original: ";
    printArray(worst, n);
    cout << endl;
    insertionSort(worst, n, comparisons, shifts);
    cout << "Sorted: ";
    printArray(worst, n);
    cout << endl;
    cout << "Comparisons: " << comparisons << " Shifts: " << shifts << endl;
 
    return 0;
}
 