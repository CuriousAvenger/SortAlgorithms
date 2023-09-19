#include <iostream>
#include <chrono>

void printArray(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int *advanceSort(int *list, int size) {
    // find max value
    int maxValue = 0;
    for (int i=0; i< size; i++) {
        if(maxValue < list[i]) {
            maxValue = list[i];
        }
    }

    // create a map like array
    int *arr = new int[maxValue+1]{};
    for (int i=0; i< size; i++) {
        arr[list[i]] += 1;
    }

    // get your final result
    int *result = new int[size];
    int iteration = 0;
    for (int i=0; i<maxValue+1; i++) {
        if (arr[i] != 0) {
            for (int j=0; j<arr[i]; j++) {
                result[iteration] = i;
                iteration++;
            }
        }
    }
    return result;
}

// Partition function for Quick Sort
int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main() {
    // defining your variables
    int list[] = {9999,1};
    const int size = sizeof(list) / sizeof(list[0]);
    
    // advance sort
    std::cout << "[+] Advance Sort Started" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    int *result = advanceSort(list, size);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    printArray(result, size);
    std::cout << "[+] Advance Sort Ended" << std::endl;
    std::cout << "[*] Execution Time: " << duration << std::endl;

    // quick sort 
    std::cout << "[+] Quick Sort Started" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    quickSort(list, 0, size-1);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();

    printArray(list, size);
    std::cout << "[+] Quick Sort Ended" << std::endl;
    std::cout << "[*] Execution Time: " << duration2 << std::endl;
    return 0;
}