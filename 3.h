#ifndef ENHANCED_STRING_SORTER_H
#define ENHANCED_STRING_SORTER_H

#include <iostream>
#include <vector>
#include <string>

struct MergeSortableString {
public:
    std::string content;
    int index;

    MergeSortableString(std::string s, int idx) : content(std::move(s)), index(idx) {}
    MergeSortableString() : index(0) {}
};

class EnhancedStringSorter {
public:
    int comparisonCount = 0;

    int quickSortStrings(std::vector<std::string>& data);
    int mergeSortStrings(std::vector<std::string>& data);
    int radixSortWithoutQS(std::vector<std::string>& data);
    int radixSortWithQS(std::vector<std::string>& data);
    int genericRadixSort(std::vector<std::string>& data, bool useQuickSortFallback);
private:
    const int TOTAL_CHARACTERS = 74;
    const int RADIX_BASE = 134;

    void executeQuickSort(std::vector<std::string>& data, int depth, int low, int high);
    std::vector<int> refinePartition(std::vector<std::string>& data, int low, int high, int depth);

    void executeMergeSort(std::vector<MergeSortableString>& data, int low, int high);
    void executeMerge(std::vector<MergeSortableString>& data, int low, int high, int mid);
    std::pair<int, int> compareWithLCP(const std::string& first, const std::string& second, int depth);

    void sortMSD(std::vector<std::string>& data, int low, int high, int depth, bool useQuickSortFallback, std::vector<std::string>& aux);
    int getCharacterCode(const std::string& str, int position);
};
#endif // ENHANCED_STRING_SORTER_H
