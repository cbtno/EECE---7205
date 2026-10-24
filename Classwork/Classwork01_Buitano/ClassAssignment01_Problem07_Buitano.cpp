#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <utility>
using namespace std;

// PROBLEM 6 ALL ALGOS
 
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << arr[i];
    }
}
 
// Bubble Sort 
void bubbleSort(int arr[], int n, long long &comparisons) {
    for (int pass = 0; pass < n - 1; pass++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - pass; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
 
// Insertion Sort 
void insertionSort(int arr[], int n, long long &comparisons) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) { arr[j + 1] = arr[j]; j--; }
            else break;
        }
        arr[j + 1] = key;
    }
}
 
// Selection Sort 
void selectionSort(int arr[], int n, long long &comparisons) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) swap(arr[i], arr[minIdx]);
    }
}
 
// Quick Sort 
int partition(int arr[], int low, int high, long long &comparisons) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) { i++; swap(arr[i], arr[j]); }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
 
void quickSortRec(int arr[], int low, int high, long long &comparisons) {
    if (low < high) {
        int p = partition(arr, low, high, comparisons);
        quickSortRec(arr, low, p - 1, comparisons);
        quickSortRec(arr, p + 1, high, comparisons);
    }
}
 
void quickSort(int arr[], int n, long long &comparisons) {
    quickSortRec(arr, 0, n - 1, comparisons);
}
 
// Merge Sort 
void merge(int arr[], int low, int mid, int high, long long &comparisons) {
    vector<int> L(arr + low, arr + mid + 1);
    vector<int> R(arr + mid + 1, arr + high + 1);
    size_t i = 0, j = 0;
    int k = low;
    while (i < L.size() && j < R.size()) {
        comparisons++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else              arr[k++] = R[j++];
    }
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}
 
void mergeSortRec(int arr[], int low, int high, long long &comparisons) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    mergeSortRec(arr, low, mid, comparisons);
    mergeSortRec(arr, mid + 1, high, comparisons);
    merge(arr, low, mid, high, comparisons);
}
 
void mergeSort(int arr[], int n, long long &comparisons) {
    mergeSortRec(arr, 0, n - 1, comparisons);
}

// Heap Sort
void siftDown(int arr[], int root, int size, long long &comparisons) {
    while (true) {
        int largest = root;
        int left = 2 * root + 1, right = 2 * root + 2;
        if (left < size)  { comparisons++; if (arr[left] > arr[largest])  largest = left; }
        if (right < size) { comparisons++; if (arr[right] > arr[largest]) largest = right; }
        if (largest == root) break;
        swap(arr[root], arr[largest]);
        root = largest;
    }
}
 
void heapSort(int arr[], int n, long long &comparisons) {
    for (int k = n / 2 - 1; k >= 0; k--) siftDown(arr, k, n, comparisons);
    for (int end = n - 1; end >= 1; end--) {
        swap(arr[0], arr[end]);
        siftDown(arr, 0, end, comparisons);
    }
}
 
typedef void (*SortFn)(int[], int, long long &);
 
struct Algorithm {
    string name;
    SortFn fn;
};
 
int main() {
    vector<Algorithm> algs = {
        {"Bubble",    bubbleSort},
        {"Insertion", insertionSort},
        {"Selection", selectionSort},
        {"Quick",     quickSort},
        {"Merge",     mergeSort},
        {"Heap",      heapSort}
    };
 
    // Comparison counts on A, sorted A, reversed A 
    const int n = 8;
    int A[n]         = {34, 7, 23, 32, 5, 62, 14, 19};
    int sortedA[n]   = {5, 7, 14, 19, 23, 32, 34, 62};
    int reversedA[n] = {62, 34, 32, 23, 19, 14, 7, 5};
    const int *inputs[3] = {A, sortedA, reversedA};
 
    cout << "Number of comparisons (n = 8)" << endl;
    cout << left << setw(12) << "Algorithm"
         << right << setw(10) << "A" << setw(10) << "Sorted" << setw(10) << "Reversed" << endl;
    cout << string(42, '-') << endl;
    for (const Algorithm &alg : algs) {
        cout << left << setw(12) << alg.name << right;
        for (int t = 0; t < 3; t++) {
            int work[n];
            for (int i = 0; i < n; i++) work[i] = inputs[t][i];   // fresh copy
            long long comps = 0;
            alg.fn(work, n, comps);
            cout << setw(10) << comps;
        }
        cout << endl;
    }
    cout << endl;
 
    // Running time on random arrays
    const int sizes[3] = {1000, 5000, 10000};
    const int maxN = 10000;
    mt19937 gen(42);                                 
    uniform_int_distribution<int> dist(1, 100000);
    vector<int> randomData(maxN);
    for (int i = 0; i < maxN; i++) randomData[i] = dist(gen);
 
    double times[6][3];     
 
    cout << "First 10 elements of each sorted array" << endl;
    for (int s = 0; s < 3; s++) {
        int size = sizes[s];
        cout << "n = " << size << ":" << endl;
        for (size_t a = 0; a < algs.size(); a++) {
            vector<int> work(randomData.begin(), randomData.begin() + size);
            long long c = 0;
 
            auto t0 = chrono::high_resolution_clock::now();
            algs[a].fn(work.data(), size, c);
            auto t1 = chrono::high_resolution_clock::now();
 
            times[a][s] = chrono::duration<double, micro>(t1 - t0).count();
 
            cout << "  " << left << setw(10) << algs[a].name << right << ": ";
            printArray(work.data(), 10);
            cout << endl;
        }
    }
    cout << endl;
 
    cout << "Running time in milliseconds" << endl;
    cout << left << setw(12) << "Algorithm" << right
         << setw(12) << "n=1000" << setw(12) << "n=5000" << setw(12) << "n=10000" << endl;
    cout << string(48, '-') << endl;
    cout << fixed << setprecision(3);
    for (size_t a = 0; a < algs.size(); a++) {
        cout << left << setw(12) << algs[a].name << right;
        for (int s = 0; s < 3; s++) cout << setw(12) << times[a][s] / 1000.0;
        cout << endl;
    }
 
    return 0;
}