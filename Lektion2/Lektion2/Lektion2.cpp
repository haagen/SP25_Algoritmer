
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

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

void selectionSort(vector<int>& arr)
{
    int n  = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = key;
    }
}

int linearSearch(const vector<int>& arr, int target)
{
    for ( int i = 0; i < arr.size(); ++i)
    {
        if (arr[i] == target) return i;
    }
    return -1;
}

int binarySearch(const vector<int>& arr, int target)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

void printVector(const vector<int>& arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main(int argc, char* argv[])
{

    vector<int> myOriginalVector = { 5, 4, 8, 2, 3, 1 };
    cout << "Original vector: ";
    printVector(myOriginalVector);

    // Bubble Sort
    vector<int> bubbelSortVector(myOriginalVector);
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(bubbelSortVector);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "BubbleSort (" << duration.count() << " ): ";
    printVector(bubbelSortVector);

    // Selection Sort
    vector<int> selectionSortVector(myOriginalVector);
    start = chrono::high_resolution_clock::now();
    selectionSort(selectionSortVector);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "SelectionSort (" << duration.count() << " ): ";
    printVector(selectionSortVector);

    // Insertion Sort
    vector<int> insertionSortVector(myOriginalVector);
    start = chrono::high_resolution_clock::now();
    insertionSort(insertionSortVector);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);    
    cout << "InsertionSort ( " << duration.count() << " ): ";
    printVector(insertionSortVector);


    auto idx = linearSearch(myOriginalVector, 3);
    cout << "LinearSeach, found on idx: " << idx << "\n";

    idx = binarySearch(insertionSortVector, 3);
    cout << "BinarySearch, found on idx: " << idx << "\n";

    idx = binarySearch(myOriginalVector, 3);
    cout << "BinarySearch (on unsorted list), found on idx: " << idx << "\n";

    std::vector<int> mySearchVector = { 96,28,28,69,36,56,94,63,61,63,11,90,14,82,87,11,81,83,12,42,2,29,71,53,15,9,75,64,83,32,77,57,9,86,4,23,75,44,5,25,30,75,5,21,45,12,53,71,27,97,16,39,11,54,12,48,6,86,66,71,56,72,70,9,91,12,4,92,39,59,53,60,50,36,5,54,20,58,40,83,34,94,75,23,32,14,51,96,22,86,93,30,9,29,29,72,36,88,51,63 };
    insertionSort(mySearchVector);
    cout << "Data size: " << mySearchVector.size() << "\n";
    start = chrono::high_resolution_clock::now();
    idx = linearSearch(mySearchVector, 88);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "LinearSearch (" << duration.count() << "), found on idx: " << idx << "\n";
    start = chrono::high_resolution_clock::now();
    idx = binarySearch(mySearchVector, 88);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "BinarySearch (" << duration.count() << "), found on idx: " << idx << "\n";
    
    return 0;
}
