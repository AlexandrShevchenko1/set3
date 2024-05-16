#include "3.h"

// ------------------------- Quick Sort -----------------------------------------

int EnhancedStringSorter::quickSortStrings(std::vector<std::string>& data) {
    comparisonCount = 0;
    executeQuickSort(data, 0, 0, data.size() - 1);
    int result = comparisonCount;
    comparisonCount = 0;
    return result;
}

void EnhancedStringSorter::executeQuickSort(std::vector<std::string>& arr, int depth, int low, int high) {
    if (high - low <= 0)
        return;
    std::vector<int> bounds = refinePartition(arr, low, high, depth);
    int newLow = bounds[0];
    int startEqual = bounds[1];
    int endEqual = bounds[2];
    executeQuickSort(arr, depth, newLow, startEqual - 1);
    executeQuickSort(arr, depth + 1, startEqual, endEqual);
    executeQuickSort(arr, depth, endEqual + 1, high);
}

std::vector<int> EnhancedStringSorter::refinePartition(std::vector<std::string>& arr, int low, int high, int depth) {
    int index = low;
    for (int i = low; i <= high; ++i) {
        if (arr[i].size() == depth)
            std::swap(arr[i], arr[index++]);
    }
    char pivot = arr[high][depth];
    low = index;
    int j = index;

    while (j <= high) {
        comparisonCount += 2;
        if (arr[j][depth] < pivot) {
            std::swap(arr[low++], arr[j++]);
            --comparisonCount;
        } else if (arr[j][depth] > pivot) {
            std::swap(arr[j], arr[high--]);
        } else {
            ++j;
        }
    }
    return {index, low, high};
}

// ------------------------- Merge Sort -----------------------------------------

int EnhancedStringSorter::mergeSortStrings(std::vector<std::string>& data) {
    comparisonCount = 0;
    int n = data.size();
    std::vector<MergeSortableString> mergeData;
    mergeData.reserve(n);
    for (int i = 0; i < n; ++i) {
        mergeData.emplace_back(data[i], 0);
    }
    executeMergeSort(mergeData, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        data[i] = mergeData[i].content;
    }
    int result = comparisonCount;
    comparisonCount = 0;
    return result;
}

void EnhancedStringSorter::executeMergeSort(std::vector<MergeSortableString>& arr, int low, int high) {
    if (low >= high)
        return;
    int mid = (low + high) >> 1;
    executeMergeSort(arr, low, mid);
    executeMergeSort(arr, mid + 1, high);
    executeMerge(arr, low, high, mid);
}

void EnhancedStringSorter::executeMerge(std::vector<MergeSortableString>& arr, int low, int high, int mid) {
    int firstIndex = low;
    int secondIndex = mid + 1;
    std::vector<MergeSortableString> tempArray(high - low + 1);
    for (size_t index = low; index <= high; index++) {
        if (firstIndex <= mid && (secondIndex > high || arr[firstIndex].index < arr[secondIndex].index)) {
            tempArray[index - low] = arr[firstIndex++];
        } else if (secondIndex <= high && (firstIndex > mid || arr[firstIndex].index > arr[secondIndex].index)) {
            tempArray[index - low] = arr[secondIndex++];
        } else {
            auto comparison = compareWithLCP(arr[firstIndex].content, arr[secondIndex].content, arr[firstIndex].index);
            if (comparison.first < 0) {
                tempArray[index - low] = arr[firstIndex++];
                arr[secondIndex].index = comparison.second;
            } else {
                tempArray[index - low] = arr[secondIndex++];
                arr[firstIndex].index = comparison.second;
            }
        }
    }
    for (int i = low; i <= high; ++i) {
        arr[i] = tempArray[i - low];
    }
}

std::pair<int, int> EnhancedStringSorter::compareWithLCP(const std::string& s1, const std::string& s2, int depth) {
    int i = depth;
    while (i < s1.length() && i < s2.length()) {
        ++comparisonCount;
        if (s1[i] != s2[i]) {
            return s1[i] < s2[i] ? std::make_pair(-1, i) : std::make_pair(1, i);
        }
        ++i;
    }
    return s1.length() == s2.length() ? std::make_pair(0, i) : (s1.length() < s2.length() ? std::make_pair(-1, i) : std::make_pair(1, i));
}

// ------------------------- Radix Sort -----------------------------------------


const int RADIX = 256;

int EnhancedStringSorter::radixSortWithQS(std::vector<std::string>& data) {
    return genericRadixSort(data, true);
}

int EnhancedStringSorter::radixSortWithoutQS(std::vector<std::string>& data) {
    return genericRadixSort(data, false);
}

int EnhancedStringSorter::genericRadixSort(std::vector<std::string>& data, bool useQuickSortFallback) {
    int n = data.size();
    std::vector<std::string> temp(n);
    comparisonCount = 0;
    sortMSD(data, 0, n - 1, 0, useQuickSortFallback, temp);
    int result = comparisonCount;
    comparisonCount = 0;
    return result;
}

void EnhancedStringSorter::sortMSD(std::vector<std::string>& data, int low, int high, int depth, bool useQuickSortFallback, std::vector<std::string>& aux) {
    if (low >= high) return;

    if (useQuickSortFallback && high - low < TOTAL_CHARACTERS) {
        executeQuickSort(data, depth, low, high);
        return;
    }

    std::vector<int> count(RADIX + 2, 0);

    for (int i = low; i <= high; ++i) {
        int c = getCharacterCode(data[i], depth);
        count[c + 2]++;
    }

    for (int r = 0; r < RADIX + 1; ++r)
        count[r + 1] += count[r];

    for (int i = low; i <= high; ++i) {
        int c = getCharacterCode(data[i], depth);
        aux[count[c + 1]++] = data[i];
    }

    for (int i = low; i <= high; ++i)
        data[i] = aux[i - low];

    for (int r = 0; r < RADIX; r++)
        sortMSD(data, low + count[r], low + count[r + 1] - 1, depth + 1, useQuickSortFallback, aux);
}

int EnhancedStringSorter::getCharacterCode(const std::string& s, int depth) {
    if (depth < s.length()) {
        return static_cast<int>(s[depth]);
    } else {
        return -1;
    }
}