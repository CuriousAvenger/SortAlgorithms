#include<iostream>
#include<vector>
#include<array>
#include<chrono>
#include<thread>
#include<mutex>
#include <cmath>

std::vector<int> sharedList;
std::mutex listMutex;

void sortSleep(int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::lock_guard<std::mutex> lock(listMutex);
    sharedList.push_back(time);
}

void printArray(double *arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::array<double, 9> list = {9,8,7,6,5,4,3,2,1};
    printArray(list.data(), list.size());
    std::cout << "Sort Algorithm Started" << std::endl;

    // function finds the maxValue
    int maxValue = 0;
    for(int i=0; i < list.size(); i++) {
        if(list[i] > maxValue) {
            maxValue = list[i];
        }
    }

    // creates threads and waits for it to finish
    std::vector<std::thread> threads;
    for(int i=0; i < list.size(); i++) {
        list[i] = static_cast<int>((list[i]/maxValue) * 1000);     
        threads.push_back(std::thread(sortSleep, list[i]));
    }
    for(auto &thread: threads) {
        thread.join();
    }

    // create your final list
    std::array<double, list.size()> result;
    std::lock_guard<std::mutex> lock(listMutex);
    int iteration = 0;
    for(const auto &value: sharedList) {
        result[iteration] = std::ceil((value*maxValue)/1000)+1;
        iteration++;
    }
    result[list.size()-1] -= 1;
    
    // print final result
    printArray(result.data(), result.size());
    return 0;
}