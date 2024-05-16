#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include <fstream>
#include "2.h"
#include "3.h"
#include "StringGenerator.h"

const std::string RANDOM_STRINGS_NAME = "Random strings";
const std::string NEARLY_SORTED_STRINGS_NAME = "Nearly sorted strings";
const std::string REVERSE_SORTED_STRINGS_NAME = "Reverse sorted strings";

std::vector<std::string> getSubarray(const std::vector<std::string>& arr, size_t subarr_size) {
    if (subarr_size > arr.size()) {
        throw std::invalid_argument("Subarray size must be less than or equal to array size");
    }
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, arr.size() - subarr_size);
    size_t start = dist(rng);
    return std::vector<std::string>(arr.begin() + start, arr.begin() + start + subarr_size);
}

int main() {
    StringGenerator generator;

    // Create test data
    const size_t dataSize = 3000;
    auto random_strings = generator.generateUnsortedStrings(dataSize);
    auto nearly_sorted_strings = generator.generateAlmostSortedStrings(dataSize);
    auto reverse_sorted_strings = generator.generateSortedStrings(dataSize);

    AdvancedSorting sorter_1;
    for (int size = 100; size <= static_cast<int>(random_strings.size()); size += 100) {
        std::vector<std::string> sub_vec = getSubarray(random_strings, size);
        auto time = std::chrono::high_resolution_clock::now();
        int comparisons = sorter_1.performQuickSort(sub_vec);
        auto elapsed = std::chrono::high_resolution_clock::now() - time;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "performQuickSort" << "," << size << "," << millisec << "," << comparisons << "\n";
    }

    for (int size = 100; size <= static_cast<int>(random_strings.size()); size += 100) {
        std::vector<std::string> sub_vec = getSubarray(random_strings, size);
        auto time = std::chrono::high_resolution_clock::now();
        int comparisons = sorter_1.performMergeSort(sub_vec);
        auto elapsed = std::chrono::high_resolution_clock::now() - time;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "performMergeSort" << "," << size << "," << millisec << "," << comparisons << "\n";
    }

    EnhancedStringSorter sorter_2;
    for (int size = 100; size <= static_cast<int>(random_strings.size()); size += 100) {
        std::vector<std::string> sub_vec = getSubarray(random_strings, size);
        auto time = std::chrono::high_resolution_clock::now();
        int comparisons = sorter_2.quickSortStrings(sub_vec);
        auto elapsed = std::chrono::high_resolution_clock::now() - time;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "quickSortStrings" << "," << size << "," << millisec << "," << comparisons << "\n";
    }

    for (int size = 100; size <= static_cast<int>(random_strings.size()); size += 100) {
        std::vector<std::string> sub_vec = getSubarray(random_strings, size);
        auto time = std::chrono::high_resolution_clock::now();
        int comparisons = sorter_2.mergeSortStrings(sub_vec);
        auto elapsed = std::chrono::high_resolution_clock::now() - time;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "mergeSortStrings" << "," << size << "," << millisec << "," << comparisons << "\n";
    }

    for (int size = 100; size <= static_cast<int>(random_strings.size()); size += 100) {
        std::vector<std::string> sub_vec = getSubarray(random_strings, size);
        auto time = std::chrono::high_resolution_clock::now();
        int comparisons = sorter_2.radixSortWithoutQS(sub_vec);
        auto elapsed = std::chrono::high_resolution_clock::now() - time;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "radixSortWithoutQS" << "," << size << "," << millisec << "," << comparisons << "\n";
    }

    for (int size = 100; size <= static_cast<int>(random_strings.size()); size += 100) {
        std::vector<std::string> sub_vec = getSubarray(random_strings, size);
        auto time = std::chrono::high_resolution_clock::now();
        int comparisons = sorter_2.radixSortWithQS(sub_vec);
        auto elapsed = std::chrono::high_resolution_clock::now() - time;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "radixSortWithQS" << "," << size << "," << millisec << "," << comparisons << "\n";
    }

    return 0;
}
