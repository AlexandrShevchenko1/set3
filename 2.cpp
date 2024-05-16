#include "2.h"
#include <algorithm>

int AdvancedSorting::performQuickSort(std::vector<std::string>& data) {
    charComparisons = 0;
    executeQuickSort(data, 0, data.size() - 1);
    int result = charComparisons;
    charComparisons = 0;
    return result;
}

int AdvancedSorting::performMergeSort(std::vector<std::string>& data) {
    charComparisons = 0;
    executeMergeSort(data, 0, data.size() - 1);
    int result = charComparisons;
    charComparisons = 0;
    return result;
}

void AdvancedSorting::executeQuickSort(std::vector<std::string>& data, int low, int high) {
    if (low < high) {
        int pivotIdx = determinePivot(data, low, high);
        executeQuickSort(data, low, pivotIdx - 1);
        executeQuickSort(data, pivotIdx + 1, high);
    }
}

void AdvancedSorting::executeMergeSort(std::vector<std::string>& data, size_t start, size_t end) {
    if (start < end) {
        size_t mid = (start + end) / 2;
        executeMergeSort(data, start, mid);
        executeMergeSort(data, mid + 1, end);
        combine(data, start, end, mid);
    }
}

void AdvancedSorting::combine(std::vector<std::string>& data, size_t start, size_t end, size_t middle) {
    std::vector<std::string> temp(end - start + 1);
    size_t left = start, right = middle + 1, k = 0;

    while (left <= middle && right <= end) {
        temp[k++] = compare(data[left], data[right]) <= 0 ? data[left++] : data[right++];
    }

    while (left <= middle) {
        temp[k++] = data[left++];
    }

    while (right <= end) {
        temp[k++] = data[right++];
    }

    for (size_t i = 0; i < temp.size(); ++i) {
        data[start + i] = temp[i];
    }
}

int AdvancedSorting::determinePivot(std::vector<std::string>& data, int low, int high) {
    std::string pivot = data[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(data[j], pivot) < 0) {
            std::swap(data[++i], data[j]);
        }
    }
    std::swap(data[i + 1], data[high]);
    return i + 1;
}

int AdvancedSorting::compare(const std::string& a, const std::string& b) {
    int minLength = std::min(a.size(), b.size());
    for (int i = 0; i < minLength; i++) {
        charComparisons++;
        if (a[i] != b[i]) {
            return a[i] < b[i] ? -1 : 1;
        }
    }
    charComparisons++;
    return a.size() < b.size() ? -1 : (a.size() > b.size() ? 1 : 0);
}
