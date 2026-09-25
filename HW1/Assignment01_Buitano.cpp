// EECE 7205 - Assignment 1
// Assignment01_Buitano.cpp
// Program containing menu for solutions to Problems 1-10

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iostream>
#include <chrono>
using namespace std;


// Problem 1: Merge Intervals

vector<vector<int>> mergeIntervals(vector<vector<int>> intervals) {
    // nothing to merge if the list is empty
    if (intervals.empty()) return {};

    // sort intervals by their start value
    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return a[0] < b[0];
         });

    // start the result with the first interval
    vector<vector<int>> result;
    result.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); i++) {
        vector<int>& last = result.back();
        vector<int>& current = intervals[i];

        // if they overlap (or touch), extend the last interval
        if (current[0] <= last[1]) {
            last[1] = max(last[1], current[1]);
        } else {
            // no overlap so add it as a new interval
            result.push_back(current);
        }
    }
    return result;
}

void runProblem1() {
    int n;
    cout << "Enter number of intervals: ";
    cin >> n;

    // read in each interval
    vector<vector<int>> intervals(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cout << "Enter start and end for interval " << i + 1 << ": ";
        cin >> intervals[i][0] >> intervals[i][1];
    }

    vector<vector<int>> merged = mergeIntervals(intervals);

    // print the merged intervals
    cout << "Merged intervals: ";
    for (auto& interval : merged) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;
}

// Problem 2: Sort Colors (Counting Sort + Dutch National Flag)

void countingSortColors(vector<int>& arr) {
    // one counter each for 0, 1, and 2
    int count[3] = {0, 0, 0};

    // count how many of each value there are
    for (int v : arr) {
        count[v]++;
    }

    // rewrite the array: all 0s, then 1s, then 2s
    int index = 0;
    for (int c = 0; c <= 2; c++) {
        for (int i = 0; i < count[c]; i++) {
            arr[index++] = c;
        }
    }
}

void dutchFlagSort(vector<int>& arr) {
    // low = end of 0s, mid = current element, high = start of 2s
    int low = 0;
    int mid = 0;
    int high = (int)arr.size() - 1;

    while (mid <= high) {
        if (arr[mid] == 0) {
            // move 0 to the front section
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == 1) {
            // 1 is already in the right spot
            mid++;
        } else {
            // move 2 to the back section, don't move mid yet
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}

void runProblem2() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " values (only 0, 1, or 2): ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // make a copy so both methods sort the same input
    vector<int> arrCopy = arr;

    countingSortColors(arr);
    cout << "Counting sort result: ";
    for (int v : arr) cout << v << " ";
    cout << endl;

    dutchFlagSort(arrCopy);
    cout << "Dutch National Flag result: ";
    for (int v : arrCopy) cout << v << " ";
    cout << endl;
}

// Problem 3: Largest Number

string largestNumber(vector<int>& nums) {
    // turn every number into a string
    vector<string> strs;
    for (int num : nums) {
        strs.push_back(to_string(num));
    }

    // put a before b if a+b makes a bigger number than b+a
    sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
        return (a + b) > (b + a);
    });

    // glue all the strings together
    string result;
    for (const string& s : strs) {
        result += s;
    }

    // if it starts with 0 then everything was 0, so just return "0"
    if (!result.empty() && result[0] == '0') {
        return "0";
    }
    return result;
}

void runProblem3() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter " << n << " nonnegative integers: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    string result = largestNumber(nums);
    cout << "Largest number: " << result << endl;
}

// PROBLEM 4: Group Anagrams

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    // key = sorted letters, value = words with those letters
    unordered_map<string, vector<string>> map;

    for (const string& word : strs) {
        // sort the letters to make the key
        string key = word;
        sort(key.begin(), key.end());
        map[key].push_back(word);
    }

    // move each group from the map into the result
    vector<vector<string>> result;
    for (auto& pair : map) {
        result.push_back(pair.second);
    }
    return result;
}

void runProblem4() {
    int n;
    cout << "Enter number of strings: ";
    cin >> n;

    vector<string> strs(n);
    cout << "Enter " << n << " strings: ";
    for (int i = 0; i < n; i++) {
        cin >> strs[i];
    }

    vector<vector<string>> groups = groupAnagrams(strs);

    // print each group on its own line
    cout << "Groups: " << endl;
    for (auto& group : groups) {
        cout << "[ ";
        for (auto& word : group) cout << word << " ";
        cout << "]" << endl;
    }
}

// Problem 5: Meeting Rooms

bool canAttendMeetings(vector<vector<int>>& intervals) {
    // 0 or 1 meetings can't conflict
    if (intervals.size() <= 1) return true;

    // sort meetings by start time
    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return a[0] < b[0];
         });

    // check each meeting against the one before it
    for (size_t i = 1; i < intervals.size(); i++) {
        // using < so meetings that touch are still ok
        if (intervals[i][0] < intervals[i - 1][1]) {
            return false;
        }
    }
    return true;
}

void runProblem5() {
    int n;
    cout << "Enter number of meetings: ";
    cin >> n;

    vector<vector<int>> intervals(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cout << "Enter start and end for meeting " << i + 1 << ": ";
        cin >> intervals[i][0] >> intervals[i][1];
    }

    bool result = canAttendMeetings(intervals);
    cout << "Can attend all meetings: " << (result ? "true" : "false") << endl;
}

// Problem 6: K Closest Points to the Origin (Sorting vs Heap)

// squared distance from (0,0), no square root needed
// long long so big numbers don't overflow
long long squaredDist(const vector<int>& p) {
    long long x = p[0];
    long long y = p[1];
    return x * x + y * y;
}

// true if point a is closer to the origin than point b
bool closerToOrigin(const vector<int>& a, const vector<int>& b) {
    return squaredDist(a) < squaredDist(b);
}

// sorting approach: sort everything and take the first k
vector<vector<int>> kClosestSort(vector<vector<int>> points, int k) {
    sort(points.begin(), points.end(), closerToOrigin);

    vector<vector<int>> result;
    for (int i = 0; i < k; i++) {
        result.push_back(points[i]);
    }
    return result;
}

// heap approach: keep only the k closest points in a max-heap
vector<vector<int>> kClosestHeap(const vector<vector<int>>& points, int k) {
    // max-heap, so the farthest point is always on top
    priority_queue<vector<int>, vector<vector<int>>, bool (*)(const vector<int>&, const vector<int>&)>
        maxHeap(closerToOrigin);

    for (const vector<int>& p : points) {
        maxHeap.push(p);
        // too many points, so remove the farthest one
        if ((int)maxHeap.size() > k) {
            maxHeap.pop();
        }
    }

    // take the points out of the heap (farthest comes out first)
    vector<vector<int>> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }
    // flip it so the closest point is first
    reverse(result.begin(), result.end());
    return result;
}

// prints points like (x,y)
void printPoints(const vector<vector<int>>& points) {
    for (const vector<int>& p : points) {
        cout << "(" << p[0] << "," << p[1] << ") ";
    }
    cout << endl;
}

// prints each point with its squared distance
void printPointsWithDistance(const vector<vector<int>>& points) {
    for (const vector<int>& p : points) {
        cout << "  (" << p[0] << "," << p[1] << ")  squared distance = "
             << squaredDist(p) << endl;
    }
}

// checks that both approaches found the same distances
bool sameDistances(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < (int)a.size(); i++) {
        if (squaredDist(a[i]) != squaredDist(b[i])) return false;
    }
    return true;
}

void runProblem6() {
    int n, k;
    cout << "Enter number of points: ";
    cin >> n;
    // need at least one point
    while (n < 1) {
        cout << "Please enter at least 1 point: ";
        cin >> n;
    }

    vector<vector<int>> points(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cout << "Enter x and y for point " << i + 1 << ": ";
        cin >> points[i][0] >> points[i][1];
    }

    // k has to be between 1 and n
    cout << "Enter k (1 to " << n << "): ";
    cin >> k;
    while (k < 1 || k > n) {
        cout << "k must be between 1 and " << n << ". Enter k: ";
        cin >> k;
    }

    // time the sorting approach
    auto sortStart = chrono::high_resolution_clock::now();
    vector<vector<int>> sortResult = kClosestSort(points, k);
    auto sortEnd = chrono::high_resolution_clock::now();

    // time the heap approach
    auto heapStart = chrono::high_resolution_clock::now();
    vector<vector<int>> heapResult = kClosestHeap(points, k);
    auto heapEnd = chrono::high_resolution_clock::now();

    // convert the times to microseconds
    long long sortTime = chrono::duration_cast<chrono::microseconds>(sortEnd - sortStart).count();
    long long heapTime = chrono::duration_cast<chrono::microseconds>(heapEnd - heapStart).count();

    cout << "Sorting approach result: ";
    printPoints(sortResult);
    printPointsWithDistance(sortResult);

    cout << "Heap approach result:    ";
    printPoints(heapResult);
    printPointsWithDistance(heapResult);

    // compare the two approaches
    cout << "\nComparison:" << endl;
    cout << "  Sorting approach time: " << sortTime << " microseconds (O(n log n))" << endl;
    cout << "  Heap approach time:    " << heapTime << " microseconds (O(n log k))" << endl;
    cout << "  Same distances found:  " << (sameDistances(sortResult, heapResult) ? "yes" : "no") << endl;
}

// Problem 7: Top K Frequent Values

// counts how many times each value shows up
unordered_map<int, int> countFrequencies(const vector<int>& nums) {
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }
    return freq;
}

// higher count goes first, if tied the smaller value goes first
bool higherFrequency(const pair<int,int>& a, const pair<int,int>& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
}

// makes a list of (value, count) sorted by frequency
vector<pair<int,int>> sortedByFrequency(const vector<int>& nums) {
    unordered_map<int, int> freq = countFrequencies(nums);

    vector<pair<int,int>> pairs(freq.begin(), freq.end());
    sort(pairs.begin(), pairs.end(), higherFrequency);
    return pairs;
}

// takes the first k values from the sorted list
vector<int> kMostFrequent(const vector<int>& nums, int k) {
    vector<pair<int,int>> pairs = sortedByFrequency(nums);

    vector<int> result;
    for (int i = 0; i < k && i < (int)pairs.size(); i++) {
        result.push_back(pairs[i].first);
    }
    return result;
}

// prints every value and its count, marks the ones picked
void printFrequencyTable(const vector<pair<int,int>>& pairs, int k) {
    cout << "Frequency table (highest first, ties -> smaller value first):" << endl;
    for (int i = 0; i < (int)pairs.size(); i++) {
        cout << "  " << pairs[i].first << " appears " << pairs[i].second
             << (pairs[i].second == 1 ? " time" : " times");
        if (i < k) cout << "   <- selected";
        cout << endl;
    }
}

// explains which values got picked if there's a tie at the cutoff
void printTieExplanation(const vector<pair<int,int>>& pairs, int k) {
    // everything was picked so there's no cutoff
    if (k >= (int)pairs.size()) return;

    // count of the last value that was picked
    int cutoffCount = pairs[k - 1].second;
    if (pairs[k].second != cutoffCount) {
        cout << "No tie at the cutoff." << endl;
        return;
    }

    // split the tied values into picked and not picked
    vector<int> chosen;
    vector<int> leftOut;
    for (int i = 0; i < (int)pairs.size(); i++) {
        if (pairs[i].second == cutoffCount) {
            if (i < k) chosen.push_back(pairs[i].first);
            else leftOut.push_back(pairs[i].first);
        }
    }

    cout << "Tie at the cutoff: these values all appear " << cutoffCount
         << (cutoffCount == 1 ? " time." : " times.") << endl;
    cout << "  Chosen (smaller values): ";
    for (int v : chosen) cout << v << " ";
    cout << endl;
    cout << "  Left out (larger values): ";
    for (int v : leftOut) cout << v << " ";
    cout << endl;
}

// prints the result with how many times each one appears
void printResultWithCounts(const vector<int>& result, const vector<int>& nums) {
    unordered_map<int, int> freq = countFrequencies(nums);
    cout << "Top " << result.size() << " frequent values with counts: ";
    for (int i = 0; i < (int)result.size(); i++) {
        if (i > 0) cout << ", ";
        cout << result[i] << " (" << freq[result[i]] << "x)";
    }
    cout << endl;
}

void runProblem7() {
    int n, k;
    cout << "Enter number of elements: ";
    cin >> n;
    // need at least one element
    while (n < 1) {
        cout << "Please enter at least 1 element: ";
        cin >> n;
    }

    vector<int> nums(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // k can't be more than the number of different values
    int distinct = (int)countFrequencies(nums).size();
    cout << "Enter k (1 to " << distinct << "): ";
    cin >> k;
    while (k < 1 || k > distinct) {
        cout << "k must be between 1 and " << distinct << ". Enter k: ";
        cin >> k;
    }

    cout << "Total elements: " << n << ", distinct values: " << distinct << endl;

    vector<pair<int,int>> pairs = sortedByFrequency(nums);
    printFrequencyTable(pairs, k);
    printTieExplanation(pairs, k);

    vector<int> result = kMostFrequent(nums, k);
    printResultWithCounts(result, nums);
    cout << "Top " << k << " frequent values: ";
    for (int v : result) cout << v << " ";
    cout << endl;
}

// Problem 8: Merge K Sorted Arrays

// one heap entry: the value, which array it's from, and its position
struct HeapEntry {
    int value;
    int arrIdx;
    int elIdx;
};

// makes the priority queue a min-heap (smallest value on top)
struct CompareEntry {
    bool operator()(const HeapEntry& a, const HeapEntry& b) {
        return a.value > b.value;
    }
};

vector<int> mergeKSortedArrays(const vector<vector<int>>& arrays) {
    priority_queue<HeapEntry, vector<HeapEntry>, CompareEntry> minHeap;

    // push the first element of each array (skip empty ones)
    for (int i = 0; i < (int)arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], i, 0});
        }
    }

    vector<int> result;
    while (!minHeap.empty()) {
        // take the smallest value
        HeapEntry top = minHeap.top();
        minHeap.pop();
        result.push_back(top.value);

        // push the next element from the same array if there is one
        if (top.elIdx + 1 < (int)arrays[top.arrIdx].size()) {
            minHeap.push({arrays[top.arrIdx][top.elIdx + 1], top.arrIdx, top.elIdx + 1});
        }
    }
    return result;
}

// checks if an array is sorted in ascending order
bool isSortedArray(const vector<int>& arr) {
    for (int i = 1; i < (int)arr.size(); i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

// prints an array, or (empty) if there's nothing in it
void printArray(const vector<int>& arr) {
    if (arr.empty()) {
        cout << "(empty)";
        return;
    }
    for (int value : arr) cout << value << " ";
}

void runProblem8() {
    int k;
    cout << "Enter number of arrays: ";
    cin >> k;
    // can't have a negative number of arrays
    while (k < 0) {
        cout << "Number of arrays cannot be negative. Enter number of arrays: ";
        cin >> k;
    }

    vector<vector<int>> arrays(k);
    for (int i = 0; i < k; i++) {
        int len;
        cout << "Enter length of array " << i + 1 << ": ";
        cin >> len;
        while (len < 0) {
            cout << "Length cannot be negative. Enter length of array " << i + 1 << ": ";
            cin >> len;
        }

        arrays[i].resize(len);
        cout << "Enter " << len << " sorted values: ";
        for (int j = 0; j < len; j++) {
            cin >> arrays[i][j];
        }

        // ask again if the array isn't sorted
        while (!isSortedArray(arrays[i])) {
            cout << "Array " << i + 1 << " is not sorted. Enter " << len << " sorted values: ";
            for (int j = 0; j < len; j++) {
                cin >> arrays[i][j];
            }
        }
    }

    vector<int> result = mergeKSortedArrays(arrays);

    cout << "Merged sorted array: ";
    printArray(result);
    cout << endl;
}

// Problem 9: Kth Largest Element (Quickselect)

int partition(vector<int>& nums, int left, int right) {
    // use the middle element as the pivot and move it to the end
    int middle = left + (right - left) / 2;
    swap(nums[middle], nums[right]);

    int pivot = nums[right];
    int i = left;
    // move everything <= pivot to the left side
    for (int j = left; j < right; j++) {
        if (nums[j] <= pivot) {
            swap(nums[i], nums[j]);
            i++;
        }
    }
    // put the pivot in its final spot
    swap(nums[i], nums[right]);
    return i;
}

int quickSelect(vector<int>& nums, int left, int right, int target) {
    // only one element left so it must be the answer
    if (left == right) return nums[left];

    int pivotIndex = partition(nums, left, right);

    if (pivotIndex == target) {
        // found it
        return nums[pivotIndex];
    } else if (target < pivotIndex) {
        // answer is on the left side
        return quickSelect(nums, left, pivotIndex - 1, target);
    } else {
        // answer is on the right side
        return quickSelect(nums, pivotIndex + 1, right, target);
    }
}

int findKthLargest(vector<int> nums, int k) {
    // kth largest is at index n - k if the array were sorted
    int target = (int)nums.size() - k;
    return quickSelect(nums, 0, (int)nums.size() - 1, target);
}

void runProblem9() {
    int n, k;
    cout << "Enter number of elements: ";
    cin >> n;
    // need at least one element
    while (n < 1) {
        cout << "Please enter at least 1 element: ";
        cin >> n;
    }

    vector<int> nums(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // k has to be between 1 and n
    cout << "Enter k (1 to " << n << "): ";
    cin >> k;
    while (k < 1 || k > n) {
        cout << "k must be between 1 and " << n << ". Enter k: ";
        cin >> k;
    }

    int result = findKthLargest(nums, k);
    cout << "The kth largest element (k = " << k << ") is: " << result << endl;
}

// Problem 10: Count Inversions

long long mergeAndCount(vector<int>& values, vector<int>& temp, int left, int mid, int right) {
    int i = left;      // index for left half
    int j = mid + 1;   // index for right half
    int k = left;      // index for temp
    long long count = 0;

    while (i <= mid && j <= right) {
        if (values[i] <= values[j]) {
            // left one is smaller or equal, not an inversion
            temp[k++] = values[i++];
        } else {
            // right one is smaller, so it's smaller than everything
            // left in the left half too
            temp[k++] = values[j++];
            count += (mid - i + 1);
        }
    }

    // copy whatever is left over
    while (i <= mid) {
        temp[k++] = values[i++];
    }
    while (j <= right) {
        temp[k++] = values[j++];
    }

    // copy the merged part back into values
    for (int p = left; p <= right; p++) {
        values[p] = temp[p];
    }
    return count;
}

long long mergeSortAndCount(vector<int>& values, vector<int>& temp, int left, int right) {
    // one element or less has no inversions
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    long long count = 0;
    // inversions in left half + right half + across both halves
    count += mergeSortAndCount(values, temp, left, mid);
    count += mergeSortAndCount(values, temp, mid + 1, right);
    count += mergeAndCount(values, temp, left, mid, right);
    return count;
}

long long countInversions(vector<int> values) {
    if (values.empty()) return 0;
    // temp array used while merging
    vector<int> temp(values.size());
    return mergeSortAndCount(values, temp, 0, (int)values.size() - 1);
}

void runProblem10() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    // can't have a negative number of elements
    while (n < 0) {
        cout << "Number of elements cannot be negative. Enter number of elements: ";
        cin >> n;
    }

    vector<int> values(n);
    if (n > 0) {
        cout << "Enter " << n << " integers: ";
    }
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    // long long because the count can get really big
    long long result = countInversions(values);
    cout << "Number of inversions: " << result << endl;
}

// MENU

void printMenu() {
    cout << "\n===== EECE 7205 Assignment 1 Menu =====\n";
    cout << "1. Merge Intervals\n";
    cout << "2. Sort Colors (Counting Sort + Dutch National Flag)\n";
    cout << "3. Largest Number by Concatenation\n";
    cout << "4. Group Anagrams\n";
    cout << "5. Can Attend All Meetings\n";
    cout << "6. K Closest Points to Origin (Sort vs Heap)\n";
    cout << "7. K Most Frequent Elements\n";
    cout << "8. Merge K Sorted Arrays\n";
    cout << "9. Kth Largest Element (Quickselect)\n";
    cout << "10. Count Inversions\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    // keep showing the menu until the user picks 0
    do {
        printMenu();
        cin >> choice;

        // run whichever problem was picked
        switch (choice) {
            case 1: runProblem1(); break;
            case 2: runProblem2(); break;
            case 3: runProblem3(); break;
            case 4: runProblem4(); break;
            case 5: runProblem5(); break;
            case 6: runProblem6(); break;
            case 7: runProblem7(); break;
            case 8: runProblem8(); break;
            case 9: runProblem9(); break;
            case 10: runProblem10(); break;
            case 0: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (choice != 0);

    return 0;
}