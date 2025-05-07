
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

/*
 *      Adding BubbleSort to be able to compare with HeapSort
 */
void bubbleSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

/*
 * MERGE SORT
 */
void merge(vector<int>& arr, int left, int mid, int right)
{
    // Check data size
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Tillfällig array
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; ++i)
    {
        R[i] = arr[mid + 1 + i];
    }
    // i räknare för vänstra arrayn, j räknare för högra arryn
    // k räknare för mål arrayen 
    int i = 0, j = 0, k = left;
    // Merga i rätt ordning från de tillfälliga arrayerna
    // Slutar vi när vi når slutet av någon av dem
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Merga på eventuellt kvarvarande data
    while (i < n1)
    {
        arr[k] = L[i];
        k++; i++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        k++; j++;
    }
}

void mergeSort(vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        // Split data in two
        int mid = left + (right - left) / 2;

        // Call mergeSort recusivly
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted arrays
        merge(arr, left, mid, right);
    }
}


/*
 * QUICK SORT
 */
int partition(vector<int>& arr, int low, int high) {
    // Sätt pivot och initiera räknare
    int pivot = arr[high];
    int leftwall = low - 1;

    // Loopa över intervallet low -> high
    for (int i = low; i < high; i++) {
        // Om pivot är större än talet, swap left
        if (arr[i] < pivot) {
            leftwall++;    
            swap(arr[leftwall], arr[i]);
        }
    }
    swap(arr[leftwall + 1], arr[high]);
    return leftwall + 1;   // Correct place for pivot
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partitionera
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/*
 * HEAP SORT
 */
void heapify(vector<int>& arr, int n, int i)
{
    int largest = i;    // Vi gissar att toppen är störst
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest])
    {
        largest = right; 
    }
    // Sätt största talet på toppen
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr)
{
    int n = arr.size();

    // Bygg Max-heap
    for (int i = n/2 -1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // Extrahera elementen från toppen (största talet -> slutet på arrayen)
    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void printVector(const vector<int>& arr)
{
    for (int i=0; i<arr.size(); ++i)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main(int argc, char* argv[])
{

    vector<int> myOriginalVector = { 23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15 };
    //vector<int> myOriginalVector = { 23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15, 23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15, 23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15, 23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15, 23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15, 23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15, 23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15, 23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15,23, 8, 13, 88, 55, 59, 6, 42, 33, 3, 78, 69, 28, 1, 5, 10, 15 };
    cout << "Original Vector: ";
    printVector(myOriginalVector);

    vector<int> mergeSortVector(myOriginalVector);
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(mergeSortVector, 0, mergeSortVector.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Merge Sort ( " << duration.count() << " ns): ";
    printVector(mergeSortVector);

    vector<int> quickSortVector(myOriginalVector);
    start = std::chrono::high_resolution_clock::now();
    quickSort(quickSortVector, 0, quickSortVector.size() - 1);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    cout << "Quick Sort ( " << duration.count() << " ns): ";
    printVector(quickSortVector);
    
    vector<int> heapSortVector(myOriginalVector);
    start = chrono::high_resolution_clock::now();
    heapSort(heapSortVector);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "Heap Sort (" << duration.count() << " ns): ";
    printVector(heapSortVector);
    
    vector<int> bubbleSortVector(myOriginalVector);
    start = chrono::high_resolution_clock::now();
    bubbleSort(bubbleSortVector);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "Bubble Sort (" << duration.count() << " ns): ";
    printVector(bubbleSortVector);
    
    return 0;
}
